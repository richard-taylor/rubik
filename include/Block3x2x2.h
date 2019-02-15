
#ifndef BLOCK3X2X2_H
#define BLOCK3X2X2_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent a solved 3x2x2 block on a cube.

It assumes that we are extending a 2x2x2 block, which is defined by
the corner slot that is already solved.

A 3x2x2 block is 2 adjacent solved corners and 5 adjacent solved edges.
*/
class Block3x2x2 : public CubePattern
{
public:
    Block3x2x2(CornerSlot fixedCorner);

    virtual bool on(const Cube &cube) const;

private:
    CornerSlot corners[3][2];
    EdgeSlot edges[3][5];
};

#endif
