
#include <iostream>
#include <stdexcept>
#include "State.h"
#include "Packer.h"

State::State(int bits) : m_bits(bits)
{
    if (bits > 8 * MAX_BYTES) 
        throw std::out_of_range("too many bits for State");
}

State::State(Packer &for_packer) : State(for_packer.state_bits())
{
}

void State::set_byte(int index, byte data)
{
    if (index < 0 || index >= MAX_BYTES)
        throw std::out_of_range("bad index for State");
        
    m_bytes[index] = data; 
}

byte State::get_byte(int index) const
{
    if (index < 0 || index >= MAX_BYTES)
        throw std::out_of_range("bad index for State");
        
    return m_bytes[index];
}
    
bool State::get_bit(int bit) const
{
    if (bit < 0 || bit >= m_bits)
        throw std::out_of_range("bad bit for State");
        
    int index = bit / 8;
    
    byte probe = 1 << (bit % 8);
    
    return (m_bytes[index] & probe) != 0;
}
