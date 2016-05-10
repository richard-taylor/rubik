
#include <cassert>
#include "CubeCacheLayer.h"

CubeCacheLayer::CubeCacheLayer(int depth) : m_depth(depth)
{
}

int CubeCacheLayer::depth() const
{
    return m_depth;
}

int CubeCacheLayer::size() const
{
    return m_map.size();
}

void CubeCacheLayer::add(const Cube &cube, const Scramble &scramble)
{
    m_map[cube] = scramble;
}
   
void CubeCacheLayer::remove(const Cube &cube, const Scramble &scramble)
{
    m_map.erase(cube);
}

bool CubeCacheLayer::contains(const Cube &cube) const
{
    return m_map.find(cube) != m_map.end();
}

Scramble CubeCacheLayer::solution(const Cube &cube) const
{
    return m_map.find(cube)->second.inverse();
}
