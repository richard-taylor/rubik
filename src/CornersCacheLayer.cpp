
#include <cassert>
#include <fstream>
#include <sstream>
#include "CornersCacheLayer.h"
#include "Cube.h"

CornersCacheLayer::CornersCacheLayer(const std::string &basename, int depth)
: m_depth(depth)
{
    std::stringstream filename;
    filename << basename << "." << depth;
    
    std::ifstream ifs(filename.str().c_str(), std::ios::in | std::ios::binary);
    if (ifs)
    {
        ifs.seekg(0, std::ios::end);
        
        int nbytes = ifs.tellg();
        m_vector.reserve(nbytes / sizeof(unsigned long long));
        
        ifs.seekg(0, std::ios::beg);
        ifs.read((char*)&m_vector[0], nbytes);
        ifs.close();
    }
}

int CornersCacheLayer::depth() const
{
    return m_depth;
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
