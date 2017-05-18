
#include <iostream>
#include "CacheBuilder.h"
#include "Cube.h"
#include "CubeCache.h"
#include "Packer.h"
#include "Scramble.h"
#include "State.h"

#define SAY(X) if (m_verbose) { std::cout << X << std::endl; }

CacheBuilder::CacheBuilder(CubeCache &cache, Packer &packer)
    : m_cache(cache),
      m_packer(packer), 
      m_verbose(false),
      m_store(false)
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

void CacheBuilder::store_twists(bool store)
{
    m_store = store;
}
    
bool CacheBuilder::store_twists() const
{
    return m_store;
}
    
void CacheBuilder::depth_first(Cube cube, Scramble scramble, Cube::Twist twist)
{
    cube.twist(twist);
    scramble.add(twist);
    
    int turns = scramble.length();
    
    State state(m_packer);
    m_packer.pack(cube, state);
    
    int status = m_cache.test_and_set(state, turns);

    bool store_twists = (m_store && status <= 0);
    
    if (store_twists)
    {
        // this is a better or equal way to get to this state so store
        // the scramble so far... if we are storing all the twists.
    }
    
    // descend further if turns was less than the previously stored value,
    // or if it was equal and we are storing all the ways to get to a state.
        
    if (status < 0 || store_twists)
    {
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
