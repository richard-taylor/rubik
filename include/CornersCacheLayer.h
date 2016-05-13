
#ifndef CORNERSCACHELAYER_H
#define CORNERSCACHELAYER_H

#include <vector>
#include "Cube.h"
#include "Scramble.h"

// implements LayerType for use in a Cache

class CornersCacheLayer
{
public:
    /**
    Create a layer of a certain depth (number of moves from solved).
    */
    CornersCacheLayer(int deep);
    
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
    
private:
    std::vector<unsigned long long> m_vector;
    int m_depth;
};

#endif
