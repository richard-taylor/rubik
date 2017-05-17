
#ifndef CUBECACHE_H
#define CUBECACHE_H

class State;

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
    CubeCache(int stateBits);
    
    int state_bits() const;
    
    /**
    How many states are stored in the cache?
    */
    int count() const;
    
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
    int m_stateBits;
};

#endif
