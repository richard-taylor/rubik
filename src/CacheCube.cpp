
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
    return 0;
}

void CacheCube::add(const Cube &cube, const Scramble &scramble)
{
}
   
void CacheCube::remove(const Cube &cube, const Scramble &scramble)
{
}

bool CacheCube::contains(const Cube &cube) const
{
    return true;
}
