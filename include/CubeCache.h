
#ifndef CUBECACHE_H
#define CUBECACHE_H

#include "Cache.h"
#include "CubeCacheLayer.h"

class CubeCache : public Cache<CubeCacheLayer>
{
public:
    /**
    Create a cache of a certain depth (number of moves from solved).
    */
    CubeCache(const std::string &basename) : Cache<CubeCacheLayer>(basename) {}
    
    /**
    Retrieve the solution for a given cube state.
    */
    Scramble solution(const Cube &cube) const
    {
        return get_layer(cube).solution(cube);
    }
};

#endif
