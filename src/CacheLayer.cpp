
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "CacheLayer.h"
#include "Cube.h"

CacheLayer::CacheLayer(const std::string &basename, int depth, int state_size)
: m_basename(basename), m_depth(depth), m_states(state_size)
{
    load();
}

int CacheLayer::depth() const
{
    return m_depth;
}

int CacheLayer::size() const
{
    return m_states; // m_states.size();
}
    
/**
Test for a cached cube state in this layer.
*/
bool CacheLayer::contains(const Cube &cube) const
{
    unsigned char state[m_states.state_size()];
    
    extract_state(cube, state);
    
    return true; // m_states.contains(state);
}

// string utilities

std::string join(const std::string &basename, int N, const std::string &suffix)
{
    std::stringstream ss;
    ss << basename << "." << N;
    
    if (suffix != "")
    {
        ss << "." << suffix;
    }
    return ss.str();
}

// optional overrides

std::string CacheLayer::name()
{
    return join(m_basename, m_depth, "");
}

// build support

void CacheLayer::load()
{
    // m_states.load(name());
}

// methods called by CacheBuilder

void CacheLayer::initialise()
{
    if (m_depth == 0)
    {
        // create the first layer
    }
    else
    {
        cubes.reset(new ifstream(join(m_basename, N - 1, "cubes").c_str(), std::ios::binary));
        temp.reset(new ofstream(join(m_basename, N, "temp").c_str(), std::ios::binary));
    }
}

bool CacheLayer::get_position(Cube &cube, Cube::Twist &twist)
{
    if (m_depth == 0)
    {
        return false;
    }
    
    cubes->read((char*)&cube, sizeof(Cube));
    cubes->read((char*)&twist, sizeof(Cube::Twist));
    
    return !cubes->eof() && cubes->good();
}

bool CacheLayer::add_position(const Cube &cube, const Cube::Twist &twist)
{     
    temp->write((char*)&cube, sizeof(Cube));
    temp->write((char*)&twist, sizeof(Cube::Twist));
    
    return temp->good();
}

void CacheLayer::finalise()
{
    // close the .temp and .cubes files.
    
    if (cubes)
    {
        cubes->close();
    }
    if (temp)
    {
        temp->close();
    }
    
    // remove duplicates from .temp and create the next .cubes file
    
    // read in what we created to this new layer
    load();  
}
