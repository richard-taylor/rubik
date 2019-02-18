
#ifndef F2LMINUS1_H
#define F2LMINUS1_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent a solved F2L-1 skeleton on a cube.

It assumes that we are extending a 3x2x2 block, which is defined by
the middle edge slot that is already solved.

F2L-1 is 3 adjacent solved corners and 7 adjacent solved edges.
*/
class F2Lminus1 : public CubePattern
{
public:
    F2Lminus1(EdgeSlot middleEdge);

    virtual bool on(const Cube &cube) const;

private:
    CornerSlot corners[4][3];
    EdgeSlot edges[4][7];

    void set(int, CornerSlot, CornerSlot, CornerSlot, EdgeSlot, EdgeSlot, EdgeSlot, EdgeSlot, EdgeSlot, EdgeSlot, EdgeSlot);
};

#endif
