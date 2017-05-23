
#ifndef CUBECACHE_H
#define CUBECACHE_H

#include <string>
class State;

/**
A cache of mappings from a fixed-size state to the minimum
number of turns to solve that state.
    
The state might be the full cube state, or a sub-state such as just
the corner positions, or just some of the edge positions.
    
Normally a Cube will be converted into a state using a Packer.
*/
class CubeCache
{
public:
    /**
    How many bits in the fixed-size state?
    */
    virtual int state_bits() const = 0;
    
    /**
    How many states are stored in the cache?
    */
    virtual int count() const = 0;
    
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
    virtual int test_and_set(const State &state, int turns) = 0;
    
    /**
    Retrieve the minumum turn solution for a given cube state.
    
    This will be between 0 and 20. Unless the state is unknown, in which
    case the return value will be -1.
    */
    virtual int solution(const State &state) const = 0;
    
    /**
    Save the cache data to a named file.
    */
    virtual bool save(const std::string filename) = 0;
};

#endif
