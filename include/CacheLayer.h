
#ifndef CACHELAYER_H
#define CACHELAYER_H

#include <fstream>
#include <string>
#include <vector>
#include "Cube.h"
#include "Scramble.h"

// abstract base class for LayerType to use in a Cache

class CacheLayer
{
public:
    /**
    A layer of a certain depth (number of moves from solved).
    */
    CacheLayer(int deep);
    
    /**
    Get the depth of the layer (number of moves from solved).
    */
    int depth() const;
    
    /**
    Count the number of states in this layer.
    */
    virtual int size() const = 0;
    
    /**
    Test for a cached cube state in this layer.
    */
    virtual bool contains(const Cube &cube) const = 0;
        
protected:
    // stuff for CacheBuilder
    
    static std::string join(const std::string &basename, int N, const std::string &suffix);
    static std::string default_name(const std::string &basename, int deep);
    static bool exists(const std::string &basename, int deep);

    static bool read_cube(std::istream &in, Cube &cube);
    static bool write_cube(std::ostream &out, const Cube &cube);
    
    static bool read_twist(std::istream &in, Cube::Twist &twist);
    static bool write_twist(std::ostream &out, const Cube::Twist &twist);
    
    static bool read_scramble(std::istream &in, Scramble &scramble, int length);
    static bool write_scramble(std::ostream &out, const Scramble &scramble);
    
private:
    int m_depth;
};

#endif
