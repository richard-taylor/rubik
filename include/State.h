
#ifndef STATE_H
#define STATE_H

#include "Typedefs.h"

class Packer;

class State
{
public:
    State(int bits);
    State(Packer &for_packer);
    
    void set_byte(int index, byte data);
    byte get_byte(int index);
    
    bool get_bit(int bit);
    
private:
    static const int MAX_BYTES = 20;
    
    int m_bits;
    byte m_bytes[MAX_BYTES];
};

#endif
