
#ifndef PACKER_H
#define PACKER_H

#include "Typedefs.h"

class Cube;

class Packer
{
public:
    virtual void pack(const Cube &cube, byte *state) = 0;    
};

#endif
