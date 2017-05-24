
#include <cstring>
#include <fstream>
#include <stdexcept>
#include "State.h"
#include "TrieCache.h"

const unsigned int UNUSED = 0xffffffff;

TrieCache::TrieCache(int stateBits, int tableSize) 
    : m_stateBits(stateBits), m_tableSize(tableSize)
{
    m_stateCount = 0;
    
    if (m_tableSize & 1)
        m_tableSize++;    // need an even number of indices
    
    if (m_tableSize < 8)
        m_tableSize = 8;  // this wont go far...
        
    m_table = new unsigned int[m_tableSize];
    
    // mark the whole table as unused
    memset(m_table, 0xff, m_tableSize * sizeof(unsigned int));
    
    // initialise the root bit
    m_table[0] = 2;
    m_table[1] = 4;
    m_tableNextFree = 6;
}

TrieCache::TrieCache(const std::string filename)
{
    m_table = NULL;
    
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (in)
    {
        in.read((char*)&m_stateBits, sizeof(m_stateBits));
        in.read((char*)&m_stateCount, sizeof(m_stateCount));
        in.read((char*)&m_tableSize, sizeof(m_tableSize));
        in.read((char*)&m_tableNextFree, sizeof(m_tableNextFree));
        
        m_table = new unsigned int[m_tableSize];
        
        in.read((char*)&m_table[0], m_tableSize * sizeof(unsigned int));
    }
    if (!in.good())
    {
        // the destructor will not be called if we throw in the constructor.
        // so we have to clean up what we allocated first.
        
        if (m_table != NULL)
            delete[] m_table;
            
        throw std::runtime_error("failed to load TrieCache");
    }
}

TrieCache::~TrieCache()
{
    delete[] m_table;
}

int TrieCache::state_bits() const
{
    return m_stateBits;
}

int TrieCache::count() const
{
    return m_stateCount;
}

int TrieCache::table_used() const
{
    return m_tableNextFree;
}

int TrieCache::table_waste() const
{
    int n = 0;
    for (int i = 0; i < m_tableNextFree; i++)
    {
        if (m_table[i] == UNUSED)
            n++;
    }
    return n;
}

int TrieCache::test_and_set(const State &state, int turns)
{
    int bit = 0;
    unsigned int position = 0;
    
    while (bit < m_stateBits - 1)
    {
        unsigned int slot = position + (state.get_bit(bit) ? 1 : 0);
        
        if (m_table[slot] == UNUSED)
        {
            if (m_tableNextFree >= m_tableSize)
                throw std::overflow_error("TrieCache table is too small.");
                
            m_table[slot] = m_tableNextFree;
            m_tableNextFree += 2;
        }
        position = m_table[slot];
        bit++;
    }
    
    unsigned int last = position + (state.get_bit(bit) ? 1 : 0);
    
    if (m_table[last] == UNUSED)
    {
        m_stateCount++;
    }
    
    unsigned int uturns = turns;
    
    if (m_table[last] > uturns)
    {
        m_table[last] = uturns;
        return -1;
    }
    return (m_table[last] == uturns) ? 0 : 1;
}
    
int TrieCache::solution(const State &state) const
{
    int bit = 0;
    unsigned int position = 0;
    
    while (bit < m_stateBits)
    {
        unsigned int slot = position + (state.get_bit(bit) ? 1 : 0);
        
        if (m_table[slot] == UNUSED)
        {
            return -1;
        }
        position = m_table[slot];
        bit++;
    }
    return position;
}
    
bool TrieCache::save(const std::string filename)
{
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (out)
    {
        out.write((char*)&m_stateBits, sizeof(m_stateBits));
        out.write((char*)&m_stateCount, sizeof(m_stateCount));
        out.write((char*)&m_tableSize, sizeof(m_tableSize));
        out.write((char*)&m_tableNextFree, sizeof(m_tableNextFree));
        
        out.write((char*)&m_table[0], m_tableSize * sizeof(unsigned int));
        
        return out.good();
    }
    return false;
}
