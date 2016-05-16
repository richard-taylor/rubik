
#include <cassert>
#include <fstream>
#include <sstream>
#include "CornersCacheLayer.h"

CornersCacheLayer::CornersCacheLayer(const std::string &basename, int depth)
: CacheLayer(depth)
{
    std::stringstream filename;
    filename << basename << "." << depth;
    
    std::ifstream ifs(filename.str().c_str(), std::ios::binary);
    if (ifs)
    {
        ifs.seekg(0, std::ios::end);
        
        int nbytes = ifs.tellg();
        int nitems = nbytes / sizeof(unsigned long long);
        
        m_vector.reserve(nitems);
        ifs.seekg(0, std::ios::beg);
        
        // TODO faster way?
        
        unsigned long long value;
        for (int i = 0; i < nitems; i++)
        {
            ifs.read((char*)&value, sizeof(unsigned long long));
            m_vector.push_back(value);
        }
        
        ifs.close();
    }
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
