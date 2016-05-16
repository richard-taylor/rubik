
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

bool CacheLayer::read_cube(std::istream &in, Cube &cube, Cube::Twist &twist)
{
    in.read((char*)&cube, sizeof(Cube));
    in.read((char*)&twist, sizeof(Cube::Twist));
    
    return !in.eof() && in.good();
}

bool CacheLayer::write_cube(std::ostream &out, const Cube &cube, const Cube::Twist &twist)
{
    out.write((char*)&cube, sizeof(Cube));
    out.write((char*)&twist, sizeof(Cube::Twist));
    
    return out.good();
}
