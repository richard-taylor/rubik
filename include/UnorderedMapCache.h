
#ifndef UNORDEREDMAPCACHE_H
#define UNORDEREDMAPCACHE_H

#include <unordered_map>
#include "CubeCache.h"
#include "Typedefs.h"

class UnorderedMapCache : public CubeCache
{
public:
    /**
    Create a cache of mappings from a fixed-size state to the minimum
    number of turns to solve that state.
    
    The state might be the full cube state, or a sub-state such as just
    the corner positions, or just some of the edge positions.
    
    Normally a Cube will be converted into a state using a Packer.
    */
    UnorderedMapCache(int stateBits);
    
    /**
    Load a previously saved cache.
    */
    UnorderedMapCache(const std::string filename);
    
    int state_bits() const;
    
    /**
    How many states are stored in the cache?
    */
    int count() const;
    
    /**
    What is the maximum turn depth stored in the cache?
    */
    int depth() const;
    void depth(int max_turns);
    
    /**
    Set the minumum turn solution for a given cube state.
    
    Turns must be between 0 and 20.
    
    The passed value is only set if the state was previously unknown, or
    if the currently stored value is greater than the passed value.
    
    The return value indicates what happened:
    
    -1 : the passed value was less than the stored value (or state unknown)
     0 : the passed value was equal to the stored value
     1 : the passed value was greater than the stored value
    */
    int test_and_set(const State &state, int turns);
    
    /**
    Retrieve the minumum turn solution for a given cube state.
    
    This will be between 0 and 20. Unless the state is unknown, in which
    case the return value will be -1.
    */
    int solution(const State &state) const;
    
    /**
    Save the cache data to a named file.
    */
    bool save(const std::string filename);
     
private:
    int m_depth;
    int m_stateBits;
    int m_stateBytes;
    
    std::unordered_map<std::string, byte> m_map;
};

#endif
