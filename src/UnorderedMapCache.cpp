
#include <cstring>
#include <fstream>
#include <stdexcept>
#include "State.h"
#include "UnorderedMapCache.h"

inline int bits_to_bytes(int bits)
{
    int bytes = bits / 8;  // if bits is an exact multiple of 8
    
    return (bytes * 8 < bits) ? bytes + 1 : bytes;
}

inline void bytes_to_string(const byte bytes[], std::string &string)
{
    for (unsigned int i = 0; i < string.length(); i++)
    {
        string[i] = bytes[i];
    }
}

UnorderedMapCache::UnorderedMapCache(int stateBits) : m_stateBits(stateBits)
{
    m_depth = 0;
    m_stateBytes = bits_to_bytes(stateBits);
}

UnorderedMapCache::UnorderedMapCache(const std::string filename)
{
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (in)
    {
        in.read((char*)&m_depth, sizeof(m_depth));
        in.read((char*)&m_stateBits, sizeof(m_stateBits));
        
        m_stateBytes = bits_to_bytes(m_stateBits);
        
        int stateCount;
        in.read((char*)&stateCount, sizeof(stateCount));

        m_map.reserve(stateCount);
        
        std::string key(m_stateBytes, '\0');
        byte record[m_stateBytes + 1];
        
        while (stateCount--)
        {
            in.read((char*)&record[0], m_stateBytes + 1);
            
            bytes_to_string(record, key);
    
            m_map.insert(std::make_pair(key, record[m_stateBytes]));
        }
    }
    if (!in.good())
    {
        throw std::runtime_error("failed to load UnorderedMapCache");
    }
}

int UnorderedMapCache::state_bits() const
{
    return m_stateBits;
}

int UnorderedMapCache::count() const
{
    return m_map.size();
}

int UnorderedMapCache::depth() const
{
    return m_depth;
}

void UnorderedMapCache::depth(int max_turns)
{
    m_depth = max_turns;
}

inline void state_to_string(const State &state, std::string &string)
{
    for (unsigned int i = 0; i < string.length(); i++)
    {
        string[i] = state.get_byte(i);
    }
}

int UnorderedMapCache::test_and_set(const State &state, int turns)
{
    std::string key(m_stateBytes, '\0');
    state_to_string(state, key);
    
    try
    {
        byte previous = m_map.at(key);
        
        if (turns < previous)
        {
            m_map[key] = byte(turns);
            return -1;
        }
        return (turns == previous) ? 0 : 1;
    }
    catch (std::out_of_range)
    {
        m_map[key] = byte(turns);
        return -1;
    }
}
    
int UnorderedMapCache::solution(const State &state) const
{
    std::string key(m_stateBytes, '\0');
    state_to_string(state, key);
    
    try
    {
        byte turns = m_map.at(key);
        return turns;
    }
    catch (std::out_of_range)
    {
        return -1;
    }
}
    
bool UnorderedMapCache::save(const std::string filename)
{
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (out)
    {
        out.write((char*)&m_depth, sizeof(m_depth));
        out.write((char*)&m_stateBits, sizeof(m_stateBits));
        
        int stateCount = m_map.size();       
        out.write((char*)&stateCount, sizeof(stateCount));
        
        for (auto const& item : m_map)
        {
            auto const& key = item.first;
            auto const& value = item.second;
            
            out.write(key.data(), m_stateBytes);
            out.write((char*)&value, 1);
        }       
        return out.good();
    }
    return false;
}
