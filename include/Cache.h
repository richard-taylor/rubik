
#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <vector>

class Cube;

template <class LayerType> class Cache
{
public:
    /**
    Load a cache from a given basename.
    
    The layers will have ".1", ".2", ".3" etc appended to the basename.
    */
    Cache(const std::string &basename);
    
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
