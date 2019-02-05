
#ifndef BLOCK2X2X2_H
#define BLOCK2X2X2_H

#include "CubePattern.h"

/**
Class to represent a solved 2x2x2 block on a cube.

A common first step in FMC is to solve a 2x2x2 block. This consists of
one solved corner and three adjacent solved edges.
*/
class Block2x2x2 : public CubePattern
{
public:
    virtual bool on(const Cube &cube) const;
};

#endif
