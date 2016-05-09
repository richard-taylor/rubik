
#ifndef CACHECUBE_H
#define CACHECUBE_H

#include <map>
#include "Cube.h"
#include "Scramble.h"

// implements LayerType for use in a Cache

class CacheCube
{
public:
    /**
    Create a layer of a certain depth (number of moves from solved).
    */
    CacheCube(int deep);
    
    /**
    Get the depth of the layer (number of moves from solved).
    */
    int depth() const;
    
    /**
    Count the number of states in this layer.
    */
    int size() const;
    
    /**
    Add a new state to this layer (and the scramble to create it).
    */
    void add(const Cube &cube, const Scramble &scramble);
    
    /**
    Remove a state from this layer (and the associated scramble).
    */
    void remove(const Cube &cube, const Scramble &scramble);
    
    /**
    Test for a cached cube state in this layer.
    */
    bool contains(const Cube &cube) const;
    
    /**
    Retrieve the scramble for a given cube state.
    */
    
private:
    std::map<Cube, Scramble> m_map;
    int m_depth;
};

#endif
