
#ifndef THREECORNERSTHREEEDGES_H
#define THREECORNERSTHREEEDGES_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent a skeleton with 3 corners and 3 edges remaining to be solved on a cube.
*/
class ThreeCornersThreeEdges : public CubePattern
{
public:
    virtual bool on(const Cube &cube) const;
};

#endif
