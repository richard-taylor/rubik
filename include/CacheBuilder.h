
#ifndef CACHEBUILDER_H
#define CACHEBUILDER_H

#include "Cube.h"
#include "Scramble.h"

class CubeCache;
class Packer;

class CacheBuilder
{
public:
    /**
    Builder for a given cache, using a packer. The packer converts a
    Cube state into a fixed-size array of bytes.
    */
    CacheBuilder(CubeCache &cache, Packer &packer);

    /**
    To print messages on stdout or not? Default is no messages.
    */    
    void verbose(bool on);
    
    /**
    Is the builder currently set to print messages or not?
    */
    bool verbose() const;
    
    /**
    To store the moves to reach each state or not? Default is not.
    */    
    void store_twists(bool store);
    
    /**
    Is the builder currently storing moves or not?
    */
    bool store_twists() const;
    
    /**
    Build a cache up to and including the given turn depth.
    */
    void build(int depth);
    
private:
    void depth_first(Cube cube, Scramble scramble, Cube::Twist twist);
    
    CubeCache &m_cache;
    Packer &m_packer;
    bool m_verbose;
    bool m_store;
    int m_depth;
};

#endif
