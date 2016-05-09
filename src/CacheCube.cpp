
#include <cassert>
#include "CacheCube.h"

CacheCube::CacheCube(int depth) : m_depth(depth)
{
}

int CacheCube::depth() const
{
    return m_depth;
}

int CacheCube::size() const
{
    return m_map.size();
}

void CacheCube::add(const Cube &cube, const Scramble &scramble)
{
    m_map[cube] = scramble;
}
   
void CacheCube::remove(const Cube &cube, const Scramble &scramble)
{
    m_map.erase(cube);
}

bool CacheCube::contains(const Cube &cube) const
{
    return m_map.find(cube) != m_map.end();
}

Scramble CacheCube::solution(const Cube &cube) const
{
    return m_map.find(cube)->second.inverse();
}
