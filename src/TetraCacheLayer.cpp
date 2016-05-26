
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include "TetraCacheLayer.h"

static void load_states(const std::string &filename, std::vector<unsigned long long> &states)
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

TetraCacheLayer::TetraCacheLayer(const std::string &basename, int depth)
: CacheLayer(depth)
{
    std::stringstream filename;
    filename << basename << "." << depth;
    
    load_states(filename.str(), m_vector);
}

int TetraCacheLayer::size() const
{
    return m_vector.size();
}

inline unsigned long long cubits(const Cube &cube)
{
    unsigned char corners[8];
    unsigned char edges[12];
    
    cube.get_pieces(corners, edges);
    
    // enum Corner { RUF, LUF, LUB, RUB, RDF, LDF, LDB, RDB };
    // enum Edge { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB };
    
    unsigned long long ruf = (unsigned long long)corners[Cube::RUF];
    unsigned long long uf  = (unsigned long long)edges[Cube::UF];
    unsigned long long luf = (unsigned long long)corners[Cube::LUF];
    unsigned long long ru  = (unsigned long long)edges[Cube::RU];
    unsigned long long rub = (unsigned long long)corners[Cube::RUB];
    unsigned long long rf  = (unsigned long long)edges[Cube::RF];
    unsigned long long rdf = (unsigned long long)corners[Cube::RDF];
    
    return ruf | (uf <<  8) | (luf << 16)
               | (ru << 24) | (rub << 32)
               | (rf << 40) | (rdf << 48);
}

bool TetraCacheLayer::contains(const Cube &cube) const
{
    unsigned long long corners = cubits(cube);
    
    std::vector<unsigned long long>::const_iterator i =
        std::lower_bound(m_vector.begin(), m_vector.end(), corners);
        
    return (i != m_vector.end() && corners == *i);
}

// stuff for CacheBuilder

bool TetraCacheLayer::write_corners(std::ostream &out, unsigned long long corners)
{
    out.write((char*)&corners, sizeof(unsigned long long));
    
    return out.good();
}

Cube TetraCacheLayer::Position::cube() const
{
    return m_cube;
}

Cube::Twist TetraCacheLayer::Position::lastTwist() const
{
    return m_twist;
}

bool TetraCacheLayer::Position::operator<(const Position &other) const
{
    return (cubits(m_cube) < cubits(other.m_cube));
}

bool TetraCacheLayer::exists(const std::string &basename, int deep)
{
    return CacheLayer::exists(basename, deep);
}

int TetraCacheLayer::make_first_layer(const std::string &basename)
{
    std::ofstream lout(default_name(basename, 0).c_str(), std::ios::binary);
    std::ofstream cout(cube_file(basename, 0).c_str(), std::ios::binary);

    unsigned long long corners = cubits(Cube());
    
    if (lout && write_corners(lout, cubits(Cube())) &&
        cout && write_cube(cout, Cube()) && write_twist(cout, Cube::Twist()))
        return 1;
            
    return 0;
}

std::string TetraCacheLayer::temp_file(const std::string &basename, int deep)
{
    return join(basename, deep, "temp");
}

std::string TetraCacheLayer::cube_file(const std::string &basename, int deep)
{
    return join(basename, deep, "cube");
}

bool TetraCacheLayer::read_position(std::istream &in, TetraCacheLayer::Position &position, int deep)
{
    read_cube(in, position.m_cube);
    read_twist(in, position.m_twist);
    
    return !in.eof() && in.good();
}

bool TetraCacheLayer::write_position(std::ostream &out,
                                       const TetraCacheLayer::Position &position,
                                       const Cube &next_cube,
                                       const Cube::Twist &next_twist)
{
    write_cube(out, next_cube);
    write_twist(out, next_twist);
}

int TetraCacheLayer::squash_temp(const std::string &basename, int deep)
{
    std::vector<TetraCacheLayer::Position> dupes;
    
    std::ifstream in(temp_file(basename, deep).c_str(), std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        
        int nbytes = in.tellg();
        int nitems = nbytes / sizeof(TetraCacheLayer::Position);
        
        dupes.reserve(nitems);
        in.seekg(0, std::ios::beg);
        
        // TODO faster way?
        
        TetraCacheLayer::Position value;
        for (int i = 0; i < nitems; i++)
        {
            in.read((char*)&value, sizeof(TetraCacheLayer::Position));
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
                unsigned long long value = cubits(dupes[i].m_cube);
                
                if (i == 0 || value != previous)
                {
                    ocube.write((char*)&dupes[i], sizeof(TetraCacheLayer::Position));
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
