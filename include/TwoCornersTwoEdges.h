
#ifndef TWOCORNERSTWOEDGES_H
#define TWOCORNERSTWOEDGES_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent a skeleton with 2 corners and 2 edges remaining to be solved on a cube.
*/
class TwoCornersTwoEdges : public CubePattern
{
public:
    virtual bool on(const Cube &cube) const;
};

#endif
