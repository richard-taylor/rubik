
#include <cassert>
#include "CubeCacheLayer.h"

CubeCacheLayer::CubeCacheLayer(const std::string &basename, int depth)
: m_depth(depth)
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

bool CubeCacheLayer::contains(const Cube &cube) const
{
    return m_map.find(cube) != m_map.end();
}

Scramble CubeCacheLayer::solution(const Cube &cube) const
{
    return m_map.find(cube)->second.inverse();
}
