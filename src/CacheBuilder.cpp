
#include <iostream>
#include "CacheBuilder.h"
#include "Cube.h"
#include "CubeCache.h"
#include "Packer.h"
#include "Scramble.h"

#define SAY(X) if (m_verbose) { std::cout << X << std::endl; }

CacheBuilder::CacheBuilder(CubeCache &cache, Packer &packer)
    : m_cache(cache),
      m_packer(packer), 
      m_verbose(false)
{
}

void CacheBuilder::verbose(bool on)
{
    m_verbose = on;
}

bool CacheBuilder::verbose() const
{
    return m_verbose;
}

void CacheBuilder::depth_first(Cube cube, Scramble scramble, Cube::Twist twist)
{
    cube.twist(twist);
    scramble.add(twist);
    
    byte state[100];
    m_packer.pack(cube, state);
    
    int best = m_cache.solution(state);
    
    if (scramble.length() < best)
    {
        m_cache.solution(state, scramble.length());
        
        if (scramble.length() < m_depth)
        {
            for (Cube::Face f = Cube::L; f <= Cube::B; f = Cube::Face(f + 1))
            {
                if (scramble.can_add(f))
                {
                    for (int t = 1; t <= 3; t++)
                    {
                        depth_first(cube, scramble, Cube::Twist(f, t));
                    }
                }
            }
        }
    }
}

void CacheBuilder::build(int depth)
{
    m_depth = depth;
    
    Cube cube;
    Scramble scramble;
    
    // start with each possible face and turn combination
    	
    for (Cube::Face f = Cube::L; f <= Cube::B; f = Cube::Face(f + 1))
    {
        for (int t = 1; t <= 3; t++)
        {
            depth_first(cube, scramble, Cube::Twist(f, t));
        }
    }
}
