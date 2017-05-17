
#include <iostream>
#include "State.h"

State::State(int bits) : m_bits(bits)
{
    m_bytes = new byte[1 + bits / 8];
}
    
State::~State()
{
    delete[] m_bytes;
}
