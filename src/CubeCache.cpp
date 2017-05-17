
#include <iostream>
#include "CubeCache.h"

CubeCache::CubeCache(int stateBits) : m_stateBits(stateBits)
{
}
    
int CubeCache::state_bits() const
{
    return m_stateBits;
}

int CubeCache::count() const
{
    return 0;
}
   
int CubeCache::test_and_set(const State &state, int turns)
{
    return -1;
}
    
int CubeCache::solution(const State &state) const
{
    return -1;
}
    
bool CubeCache::save(const std::string filename)
{
    return false;
}
