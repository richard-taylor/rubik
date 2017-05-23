
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "State.h"
#include "TrieCache.h"

int main()
{
    // is an int 32 bits?
    assert(sizeof(int) == 4);
    
    TrieCache cache(10, 2048);
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
	
	// too small a backing table throws an exception
	TrieCache tiny(8, 8);
	State state8(8);
	try
	{
	    state8.set_byte(0, 0);
	    tiny.test_and_set(state, 20);
	    assert(false);
	}
	catch (std::overflow_error) {}
}
