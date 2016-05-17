
#include <algorithm>
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

struct Position
{
    Cube cube;
    Cube::Twist twist;
    
    bool operator<(const Position &other) const
    {
        return (cube < other.cube);
    }
};

int CacheLayer::squash_cubes(const std::string &cube_max, const std::string &cubefile)
{
    std::vector<Position> dupes;
    
    std::ifstream in(cube_max.c_str(), std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        
        int nbytes = in.tellg();
        int nitems = nbytes / sizeof(Position);
        
        dupes.reserve(nitems);
        in.seekg(0, std::ios::beg);
        
        // TODO faster way?
        
        Position value;
        for (int i = 0; i < nitems; i++)
        {
            in.read((char*)&value, sizeof(Position));
            dupes.push_back(value);
        }
        
        in.close();
    }
    
    std::sort(dupes.begin(), dupes.end());
 
    int written = 0;
       
    std::ofstream out(cubefile.c_str(), std::ios::binary);
    if (out)
    {
        Cube previous;
        
        for (int i = 0; i < dupes.size(); ++i)
        {
            Cube value = dupes[i].cube;
            
            if (i == 0 || value != previous)
            {
                out.write((char*)&dupes[i], sizeof(Position));
                previous = value;
                ++written;
            }
        }
        out.close();
    }
    return written;
}
