
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

int CornersCacheLayer::squash_states(const std::string &state_max, const std::string &statefile)
{
    std::vector<unsigned long long> dupes;
    load_states(state_max, dupes);
    
    std::sort(dupes.begin(), dupes.end());
 
    int written = 0;
       
    std::ofstream out(statefile.c_str(), std::ios::binary);
    if (out)
    {
        unsigned long long previous = 0;
        
        for (int i = 0; i < dupes.size(); ++i)
        {
            unsigned long long value = dupes[i];
            
            if (i == 0 || value != previous)
            {
                out.write((char*)&value, sizeof(unsigned long long));
                previous = value;
                ++written;
            }
        }
        out.close();
    }
    return written;
}

int CornersCacheLayer::squash_cubes(const std::string &cube_max, const std::string &cubefile)
{
    return CacheLayer::squash_cubes(cube_max, cubefile);
}
