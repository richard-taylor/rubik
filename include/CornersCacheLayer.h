
#ifndef CORNERSCACHELAYER_H
#define CORNERSCACHELAYER_H

#include <fstream>
#include "CacheLayer.h"
#include "Cube.h"

// implements LayerType for use in a Cache

class CornersCacheLayer : public CacheLayer
{
public:
    /**
    Load a layer of a certain depth (number of moves from solved).
    */
    CornersCacheLayer(const std::string &basename, int deep);
    
    /**
    Count the number of states in this layer.
    */
    int size() const;
    
    /**
    Test for a cached cube state in this layer.
    */
    bool contains(const Cube &cube) const;
    
    /**
    Write a cube state to a binary stream.
    */
    static void write_state(std::ostream &out, const Cube &cube);
    
    /**
    Write a cube and its last twist to a binary stream.
    */
    static void write_cube(std::ostream &out, const Cube &cube, const Cube::Twist &twist);
    
private:
    std::vector<unsigned long long> m_vector;
};

#endif
