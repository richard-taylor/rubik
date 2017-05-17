
#ifndef CUBEPACKER_H
#define CUBEPACKER_H

#include "Packer.h"

class CubePacker : public Packer
{
public:
    int state_bits();
    
    void pack(const Cube &cube, State &state);
};

#endif
