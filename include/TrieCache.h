
#ifndef TRIECACHE_H
#define TRIECACHE_H

#include "CubeCache.h"

class TrieCache : public CubeCache
{
public:
    /**
    Create a cache of mappings from a fixed-size state to the minimum
    number of turns to solve that state.
    
    The state might be the full cube state, or a sub-state such as just
    the corner positions, or just some of the edge positions.
    
    Normally a Cube will be converted into a state using a Packer.
    
    The size of the backing table can also be set (if known).
    */
    TrieCache(int stateBits, int tableSize = 1000000);
    ~TrieCache();
    
    /**
    Load a previously saved cache.
    */
    TrieCache(const std::string filename);
    
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
    How much of the backing table was used?
    
    This is the smallest value which could have been passed in to
    the constructor without error. It is also the value which wastes
    least space. If a cache is saved to file and read back in, this is
    the table size allocated.
    */
    int table_used() const;
    int table_waste() const;
    
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
    int m_stateCount;

    int m_tableSize;
    int m_tableNextFree;
    
    unsigned int *m_table;
};

#endif
