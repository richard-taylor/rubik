
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "State.h"
#include "UnorderedMapCache.h"

int main()
{
    UnorderedMapCache cache(10);
    State state(10);
    
    for (int i = 0; i < 1024; i++)
    {
        state.set_byte(0, i & 0x00ff);
        state.set_byte(1, (i & 0xff00) >> 8);
        
        // new state
        assert(cache.test_and_set(state, 12) == -1);
        assert(cache.count() == i + 1);
        assert(cache.solution(state) == 12);
    }
	
	// existing state
	state.set_byte(0, 23);
	state.set_byte(1, 0);
	
	// higher turn count
	assert(cache.test_and_set(state, 13) == 1);
	assert(cache.count() == 1024);
	assert(cache.solution(state) == 12);
	
	// same turn count
	assert(cache.test_and_set(state, 12) == 0);
	assert(cache.count() == 1024);
	assert(cache.solution(state) == 12);
	
	// lower turn count
	assert(cache.test_and_set(state, 11) == -1);
	assert(cache.count() == 1024);
	assert(cache.solution(state) == 11);
	
	// save to file and reload into another cache
	assert(cache.save("/tmp/t_UnorderedMapCache.binary"));
	
	UnorderedMapCache loaded("/tmp/t_UnorderedMapCache.binary");
	assert(loaded.state_bits() == 10);
	assert(loaded.count() == 1024);
	assert(loaded.solution(state) == 11);
	
	// load from non-existent file throws an exception
	try
	{
	    UnorderedMapCache busted("no such file");
	    assert(false);
	}
	catch (std::runtime_error) {}
}
