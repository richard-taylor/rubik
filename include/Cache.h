
#ifndef CACHE_H
#define CACHE_H

#include <vector>

class Cube;

template <class LayerType> class Cache
{
public:
    /**
    Create a cache of a certain depth (number of moves from solved).
    */
    Cache(int deep);
    
    /**
    Get the maximum depth in the cache (number of moves from solved).
    */
    int depth() const;
    
    /**
    Count the number of states at a particular depth.
    */
    int count(int deep);
    
    /**
    Test for a cached cube state at any depth, or a particular depth.
    */
    bool contains(const Cube &cube, int deep = -1) const;
    
protected:
    /**
    Get the layer that contains a cached state.
    */
    const LayerType& get_layer(const Cube &cube) const;
    
private:
    std::vector<LayerType> layers;
    
    int layer(const Cube &cube) const;
};

#include "Cache.impl"
#endif
