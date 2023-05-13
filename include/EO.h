
#ifndef EO_H
#define EO_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent EO solved on a cube.

EO means that all edges are oriented with respect to one of
the axes - x, y or z.
*/
class EO : public CubePattern
{
public:
    virtual bool on(const Cube &cube) const;
};

#endif
