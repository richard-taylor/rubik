
#ifndef PACKER_H
#define PACKER_H

class Cube;
class State;

class Packer
{
public:
    virtual int state_bits() = 0;
    
    virtual void pack(const Cube &cube, State &state) = 0;    
};

#endif
