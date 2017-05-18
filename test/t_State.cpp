
#include <cassert>
#include <stdexcept>
#include "State.h"

int main()
{
    // 12-bit state
    State state12(12);
    state12.set_byte(0, 255);
    state12.set_byte(1, 15);
    
    assert(state12.get_bit(0));
    assert(state12.get_bit(1));
    assert(state12.get_bit(2));
    assert(state12.get_bit(3));
    assert(state12.get_bit(4));
    assert(state12.get_bit(5));
    assert(state12.get_bit(6));
    assert(state12.get_bit(7));
    assert(state12.get_bit(8));
    assert(state12.get_bit(9));
    assert(state12.get_bit(10));
    assert(state12.get_bit(11));
    
    // anything outside [0, 11] is a range error
    try {
        state12.get_bit(-1);
        assert(false);
    }
    catch (std::out_of_range) {}
    
    try {
        state12.get_bit(12);
        assert(false);
    }
    catch (std::out_of_range) {}
    
    // 120-bit state
    State state120(120);
    state120.set_byte(10, 149); // 128 + 16 + 4 + 1 => 10010101
    
    assert(state120.get_bit(80) == true);
    assert(state120.get_bit(81) == false);
    assert(state120.get_bit(82) == true);
    assert(state120.get_bit(83) == false);
    assert(state120.get_bit(84) == true);
    assert(state120.get_bit(85) == false);
    assert(state120.get_bit(86) == false);
    assert(state120.get_bit(87) == true);
}
