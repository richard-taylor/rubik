
#include <cassert>
#include "CornersCacheLayer.h"

CornersCacheLayer::CornersCacheLayer(int depth) : m_depth(depth)
{
}

int CornersCacheLayer::depth() const
{
    return m_depth;
}

int CornersCacheLayer::size() const
{
    return m_vector.size();
}

void CornersCacheLayer::add(const Cube &cube, const Scramble &scramble)
{
    unsigned long long corners = cube.corner_bits();
    
    std::vector<unsigned long long>::iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), corners);
        
    if (i == m_vector.end() || corners < *i)
        m_vector.insert(i, corners);
}
   
void CornersCacheLayer::remove(const Cube &cube, const Scramble &scramble)
{
    unsigned long long corners = cube.corner_bits();
    
    std::vector<unsigned long long>::iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), corners);
        
    if (i != m_vector.end() && corners == *i)
        m_vector.erase(i);
}

bool CornersCacheLayer::contains(const Cube &cube) const
{
    unsigned long long corners = cube.corner_bits();
    
    std::vector<unsigned long long>::const_iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), corners);
        
    return (i != m_vector.end() && corners == *i);
}
