
#ifndef CACHELAYER_H
#define CACHELAYER_H

#include <fstream>
#include <string>
#include <vector>
#include "Cube.h"

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
    static bool read_cube(std::istream &in, Cube &cube, Cube::Twist &twist);
    static bool write_cube(std::ostream &out, const Cube &cube, const Cube::Twist &twist);
    
    static int squash_cubes(const std::string &cube_max, const std::string &cubefile);
    
private:
    int m_depth;
};

#endif
