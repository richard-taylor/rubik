
#ifndef DR_H
#define DR_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent DR solved on a cube.

DR (domino reduction) means that the cube can be solved
using the group {U2, D2, L, R, F2, B2} for the LR (x) axis,
using the group {U, D, L2, R2, F2, B2} for the UD (y) axis,
using the group {U2, D2, L2, R2, F, B} for the FB (z) axis.
*/
class DR : public CubePattern
{
public:
    DR(Axis axis);

    virtual bool on(const Cube &cube) const;

private:
    Axis axis;
};

#endif
