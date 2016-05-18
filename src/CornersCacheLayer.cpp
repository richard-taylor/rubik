
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include "CornersCacheLayer.h"

void load_states(const std::string &filename, std::vector<unsigned long long> &states)
{
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    if (ifs)
    {
        ifs.seekg(0, std::ios::end);
        
        int nbytes = ifs.tellg();
        int nitems = nbytes / sizeof(unsigned long long);
        
        states.reserve(nitems);
        ifs.seekg(0, std::ios::beg);
        
        // TODO faster way?
        
        unsigned long long value;
        for (int i = 0; i < nitems; i++)
        {
            ifs.read((char*)&value, sizeof(unsigned long long));
            states.push_back(value);
        }
        
        ifs.close();
    }
}

CornersCacheLayer::CornersCacheLayer(const std::string &basename, int depth)
: CacheLayer(depth)
{
    std::stringstream filename;
    filename << basename << "." << depth;
    
    load_states(filename.str(), m_vector);
}

int CornersCacheLayer::size() const
{
    return m_vector.size();
}

bool CornersCacheLayer::contains(const Cube &cube) const
{
    unsigned long long corners = cube.corner_bits();
    
    std::vector<unsigned long long>::const_iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), corners);
        
    return (i != m_vector.end() && corners == *i);
}

void CornersCacheLayer::write_state(std::ostream &out, const Cube &cube)
{
    unsigned long long corners = cube.corner_bits();
    
    out.write((char*)&corners, sizeof(unsigned long long));
}

bool CornersCacheLayer::read_cube(std::istream &in, Cube &cube, Cube::Twist &twist)
{
    return CacheLayer::read_cube(in, cube, twist);
}

bool CornersCacheLayer::write_cube(std::ostream &out, const Cube &cube, const Cube::Twist &twist)
{
    return CacheLayer::write_cube(out, cube, twist);
}

struct Position
{
    Cube cube;
    Cube::Twist twist;
    
    bool operator<(const Position &other) const
    {
        return (cube.corner_bits() < other.cube.corner_bits());
    }
};

int CornersCacheLayer::squash_states(const std::string &state_max, const std::string &statefile, const std::string &cubefile)
{
    std::vector<Position> dupes;
    
    std::ifstream in(state_max.c_str(), std::ios::binary);
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
       
    std::ofstream ocube(cubefile.c_str(), std::ios::binary);
    if (ocube)
    {
        std::ofstream ostate(statefile.c_str(), std::ios::binary);
        if (ostate)
        {
            unsigned long long previous = 0;
        
            for (int i = 0; i < dupes.size(); ++i)
            {
                unsigned long long value = dupes[i].cube.corner_bits();
                
                if (i == 0 || value != previous)
                {
                    ocube.write((char*)&dupes[i], sizeof(Position));
                    ostate.write((char*)&value, sizeof(unsigned long long));
                    previous = value;
                    ++written;
                }
            }
            ostate.close();
        }
        ocube.close();
    }
    return written;
}
