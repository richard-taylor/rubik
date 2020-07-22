
#ifndef EOLINE_H
#define EOLINE_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent a solved EO Line on a cube.

EO means that all edges are oriented (with respect to the z-axis) and
Line means that the DF and DB edges are in the right place.
*/
class EOLine : public CubePattern
{
public:
    virtual bool on(const Cube &cube) const;
};

#endif
