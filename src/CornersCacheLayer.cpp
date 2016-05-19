
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

// stuff for CacheBuilder

bool CornersCacheLayer::write_corners(std::ostream &out, unsigned long long corners)
{
    out.write((char*)&corners, sizeof(unsigned long long));
    
    return out.good();
}

Cube CornersCacheLayer::Position::cube() const
{
    return m_cube;
}

Cube::Twist CornersCacheLayer::Position::lastTwist() const
{
    return m_twist;
}

bool CornersCacheLayer::Position::operator<(const Position &other) const
{
    return (m_cube < other.m_cube);
}

bool CornersCacheLayer::exists(const std::string &basename, int deep)
{
    return CacheLayer::exists(basename, deep);
}

int CornersCacheLayer::make_first_layer(const std::string &basename)
{
    std::ofstream lout(default_name(basename, 0).c_str(), std::ios::binary);
    std::ofstream cout(cube_file(basename, 0).c_str(), std::ios::binary);

    unsigned long long corners = Cube().corner_bits();
    
    if (lout && write_corners(lout, Cube().corner_bits()) &&
        cout && write_cube(cout, Cube()) && write_twist(cout, Cube::Twist()))
        return 1;
            
    return 0;
}

std::string CornersCacheLayer::temp_file(const std::string &basename, int deep)
{
    return join(basename, deep, "temp");
}

std::string CornersCacheLayer::cube_file(const std::string &basename, int deep)
{
    return join(basename, deep, "cube");
}

bool CornersCacheLayer::read_position(std::istream &in, CornersCacheLayer::Position &position)
{
    read_cube(in, position.m_cube);
    read_twist(in, position.m_twist);
    
    return !in.eof() && in.good();
}

bool CornersCacheLayer::write_position(std::ostream &out,
                                       const CornersCacheLayer::Position &position,
                                       const Cube &next_cube,
                                       const Cube::Twist &next_twist)
{
    write_cube(out, next_cube);
    write_twist(out, next_twist);
}

int CornersCacheLayer::squash_temp(const std::string &basename, int deep)
{
    std::vector<CornersCacheLayer::Position> dupes;
    
    std::ifstream in(temp_file(basename, deep).c_str(), std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        
        int nbytes = in.tellg();
        int nitems = nbytes / sizeof(CornersCacheLayer::Position);
        
        dupes.reserve(nitems);
        in.seekg(0, std::ios::beg);
        
        // TODO faster way?
        
        CornersCacheLayer::Position value;
        for (int i = 0; i < nitems; i++)
        {
            in.read((char*)&value, sizeof(CornersCacheLayer::Position));
            dupes.push_back(value);
        }
        
        in.close();
    }
    
    std::sort(dupes.begin(), dupes.end());
 
    int written = 0;
       
    std::ofstream ocube(cube_file(basename, deep).c_str(), std::ios::binary);
    if (ocube)
    {
        std::ofstream ostate(default_name(basename, deep).c_str(), std::ios::binary);
        if (ostate)
        {
            unsigned long long previous = 0;
        
            for (int i = 0; i < dupes.size(); ++i)
            {
                unsigned long long value = dupes[i].m_cube.corner_bits();
                
                if (i == 0 || value != previous)
                {
                    ocube.write((char*)&dupes[i], sizeof(CornersCacheLayer::Position));
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
