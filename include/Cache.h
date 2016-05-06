
#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <vector>
#include "Cube.h"
#include "Scramble.h"

class Cache
{
public:
    /**
    Create an empty cache.
    */
    Cache();
    
    /**
    Get the depth of the cache (number of moves from solved).
    */
    int depth() const;
    
    /**
    Extend the cache to a greater depth.
    */
    void extend(int deep);
    
    /**
    Count the number of cubes at a particular depth.
    */
    int count(int deep);
    
    /**
    Test for a cached position at any depth, or a particular depth.
    */
    bool contains(const Cube &cube, int deep = -1) const;
    
    /**
    Return an optimal solution for a given cube in the cache.
    */
    Scramble solution(const Cube &cube) const;

private:
    typedef std::map<Cube, Scramble> Layer;
    void next_layer(const Layer &previous, Layer &next);
    
    std::vector<Layer> layers;
};

#endif
