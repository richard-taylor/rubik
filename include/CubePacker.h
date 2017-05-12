
#ifndef CUBEPACKER_H
#define CUBEPACKER_H

#include "Packer.h"

class CubePacker : public Packer
{
public:
    void pack(const Cube &cube, byte *state);
    
    static const int BITS = 88;    
};

#endif
