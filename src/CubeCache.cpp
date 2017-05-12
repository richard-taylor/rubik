
#include <iostream>
#include "CubeCache.h"

CubeCache::CubeCache(int stateBits) : m_stateBits(stateBits)
{
}
    
int CubeCache::stateBits() const
{
    return m_stateBits;
}
    
int CubeCache::test_and_set(const byte *state, int turns)
{
    return -1;
}
    
int CubeCache::solution(const byte *state) const
{
    return -1;
}
    
bool CubeCache::save(const std::string filename)
{
    return false;
}
