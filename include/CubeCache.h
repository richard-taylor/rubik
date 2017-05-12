
#ifndef CUBECACHE_H
#define CUBECACHE_H

#include "Typedefs.h"

class CubeCache
{
public:
    /**
    Create a cache of mappings from a fixed-size state to the minimum
    number of turns to solve that state.
    
    The state might be the full cube state, or a sub-state such as just
    the corner positions, or just some of the edge positions.
    
    Normally a Cube will be converted into a state using a Packer.
    */
    CubeCache(int stateSize);
    
    int stateSize() const;
    
    /**
    Set the minumum turn solution for a given cube state.
    
    Turns must be between 0 and 20.
    */
    void solution(const byte *state, int turns);
    
    /**
    Retrieve the minumum turn solution for a given cube state.
    
    This will be between 0 and 20. Unless the state is unknown, in which
    case the return value will be -1.
    */
    int solution(const byte *state) const;
    
    /**
    Save the cache data to a named file.
    */
    bool save(const std::string filename);
     
private:
    int m_stateSize;
};

#endif
