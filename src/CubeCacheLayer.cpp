
#include <algorithm>
#include <cassert>
#include "CubeCacheLayer.h"

CubeCacheLayer::CubeCacheLayer(const std::string &basename, int depth)
: CacheLayer(depth)
{
}

int CubeCacheLayer::size() const
{
    return m_vector.size();
}

bool CubeCacheLayer::contains(const Cube &cube) const
{
    CubeCacheLayer::Position pos;
    pos.m_cube = cube;
    
    std::vector<CubeCacheLayer::Position>::const_iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), pos);
        
    return (i != m_vector.end() && cube == i->m_cube);
}

Scramble CubeCacheLayer::solution(const Cube &cube) const
{
    CubeCacheLayer::Position pos;
    pos.m_cube = cube;
    
    std::vector<CubeCacheLayer::Position>::const_iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), pos);
        
    return i->m_scramble.inverse();
}

// nested class Position

Cube CubeCacheLayer::Position::cube() const
{
    return m_cube;
}
        
Cube::Twist CubeCacheLayer::Position::lastTwist() const
{
    return m_scramble.last();
}
        
bool CubeCacheLayer::Position::operator<(const Position &other) const
{
    return (m_cube < other.m_cube);
}

// static methods for CacheBuilder

bool CubeCacheLayer::exists(const std::string &basename, int deep)
{
    return CacheLayer::exists(basename, deep);
}

int CubeCacheLayer::make_first_layer(const std::string &basename)
{
    std::string filename = default_name(basename, 0);
            
    std::ofstream lout(filename.c_str(), std::ios::binary);

    if (lout && write_cube(lout, Cube()) && write_scramble(lout, Scramble()))
        return 1;
            
    return 0;
}

std::string CubeCacheLayer::temp_file(const std::string &basename, int deep)
{
    return join(basename, deep, "temp");
}

std::string CubeCacheLayer::cube_file(const std::string &basename, int deep)
{
    return default_name(basename, deep);
}

bool CubeCacheLayer::read_position(std::istream &in, CubeCacheLayer::Position &position)
{
    read_cube(in, position.m_cube);
    read_scramble(in, position.m_scramble);
    
    return !in.eof() && in.good();
}

bool CubeCacheLayer::write_position(std::ostream &out, const Position &position, const Cube &next_cube, const Cube::Twist &next_twist)
{
    write_cube(out, next_cube);
    
    Scramble next_scramble = position.m_scramble;
    next_scramble.add(next_twist);
    
    write_scramble(out, next_scramble);
}

int CubeCacheLayer::squash_temp(const std::string &basename, int deep)
{
    std::vector<CubeCacheLayer::Position> dupes;
    
    std::ifstream in(temp_file(basename, deep).c_str(), std::ios::binary);
    
    CubeCacheLayer::Position position;
    
    while (read_cube(in, position.m_cube) && read_scramble(in, position.m_scramble))
    {
        dupes.push_back(position);
    }
    in.close();
    
    std::sort(dupes.begin(), dupes.end());
 
    int written = 0;
       
    std::ofstream out(cube_file(basename, deep).c_str(), std::ios::binary);
    if (out)
    {
        Cube previous;
        
        for (int i = 0; i < dupes.size(); ++i)
        {
            Cube value = dupes[i].m_cube;
                
            if (i == 0 || value != previous)
            {
                write_cube(out, value);
                write_scramble(out, dupes[i].m_scramble);
                previous = value;
                ++written;
            }
        }
        out.close();
    }
    return written;
}
