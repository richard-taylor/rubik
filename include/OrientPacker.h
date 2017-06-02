
#ifndef ORIENTPACKER_H
#define ORIENTPACKER_H

#include "Packer.h"

class OrientPacker : public Packer
{
public:
    int state_bits();
    
    void pack(const Cube &cube, State &state);
};

#endif
