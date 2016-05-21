
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "CacheLayer.h"
#include "Cube.h"

CacheLayer::CacheLayer(int depth) : m_depth(depth)
{
}

int CacheLayer::depth() const
{
    return m_depth;
}

// static methods for CacheBuilder

std::string CacheLayer::join(const std::string &basename, int N, const std::string &suffix)
{
    std::stringstream ss;
    ss << basename << "." << N;
    
    if (suffix != "")
    {
        ss << "." << suffix;
    }
    return ss.str();
}

std::string CacheLayer::default_name(const std::string &basename, int deep)
{
    return join(basename, deep, "");
}

bool CacheLayer::exists(const std::string &basename, int deep)
{
    struct stat buffer;   
    return (stat(default_name(basename, deep).c_str(), &buffer) == 0);
}

bool CacheLayer::read_cube(std::istream &in, Cube &cube)
{
    in.read((char*)&cube, sizeof(Cube));
    return !in.eof() && in.good();
}

bool CacheLayer::write_cube(std::ostream &out, const Cube &cube)
{
    out.write((char*)&cube, sizeof(Cube));
    return out.good();
}

bool CacheLayer::read_twist(std::istream &in, Cube::Twist &twist)
{
    in.read((char*)&twist, sizeof(Cube::Twist));
    return !in.eof() && in.good();
}

bool CacheLayer::write_twist(std::ostream &out, const Cube::Twist &twist)
{
    out.write((char*)&twist, sizeof(Cube::Twist));
    return out.good();
}
    
bool CacheLayer::read_scramble(std::istream &in, Scramble &scramble, int length)
{
    return scramble.read(in, length);
}

bool CacheLayer::write_scramble(std::ostream &out, const Scramble &scramble)
{
    return scramble.write(out);
}
