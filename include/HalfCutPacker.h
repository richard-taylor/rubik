
#ifndef HALFCUTPACKER_H
#define HALFCUTPACKER_H

#include "Packer.h"

class HalfCutPacker : public Packer
{
public:
    int state_bits();
    
    void pack(const Cube &cube, State &state);
};

#endif
