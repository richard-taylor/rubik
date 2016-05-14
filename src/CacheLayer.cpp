
#include <cassert>
#include <fstream>
#include "CacheLayer.h"
#include "Cube.h"

CacheLayer::CacheLayer(int depth) : m_depth(depth)
{
}

int CacheLayer::depth() const
{
    return m_depth;
}
