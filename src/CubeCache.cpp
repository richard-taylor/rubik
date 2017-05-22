
#include <cstring>
#include <iostream>
#include <stdexcept>
#include "CubeCache.h"
#include "State.h"

const unsigned int UNUSED = 0xffffffff;

CubeCache::CubeCache(int stateBits, int tableSize) 
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

CubeCache::~CubeCache()
{
    delete[] m_table;
}

int CubeCache::state_bits() const
{
    return m_stateBits;
}

int CubeCache::count() const
{
    return m_stateCount;
}

int CubeCache::table_used() const
{
    return m_tableNextFree;
}
  
int CubeCache::test_and_set(const State &state, int turns)
{
    int bit = 0;
    unsigned int position = 0;
    
    while (bit < m_stateBits - 1)
    {
        unsigned int slot = position + (state.get_bit(bit) ? 1 : 0);
        
        if (m_table[slot] == UNUSED)
        {
            if (m_tableNextFree >= m_tableSize)
                throw std::overflow_error("CubeCache table is too small.");
                
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
        
    if (m_table[last] > turns)
    {
        m_table[last] = turns;
        return -1;
    }
    return (m_table[last] == turns) ? 0 : 1;
}
    
int CubeCache::solution(const State &state) const
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
    
bool CubeCache::save(const std::string filename)
{
    return false;
}
