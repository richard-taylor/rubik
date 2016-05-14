
#ifndef CUBECACHELAYER_H
#define CUBECACHELAYER_H

#include <map>
#include <string>
#include "Cube.h"
#include "Scramble.h"

// implements LayerType for use in a Cache

class CubeCacheLayer
{
public:
    /**
    Load a layer of a certain depth (number of moves from solved).
    */
    CubeCacheLayer(const std::string &basename, int deep);
    
    /**
    Get the depth of the layer (number of moves from solved).
    */
    int depth() const;
    
    /**
    Count the number of states in this layer.
    */
    int size() const;
    
    /**
    Test for a cached cube state in this layer.
    */
    bool contains(const Cube &cube) const;
    
    /**
    Retrieve the solution for a given cube state.
    */
    Scramble solution(const Cube &cube) const;
    
private:
    std::map<Cube, Scramble> m_map;
    int m_depth;
};

#endif
