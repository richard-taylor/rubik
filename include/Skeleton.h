
#ifndef SKELETON_H
#define SKELETON_H

#include "CubePattern.h"
#include "Enums.h"

/**
Class to represent a cube solved except for a small number of corners and/or edges.

This is known as a skeleton in FMC and is defined by the number of unsolved corners and edges.
*/
class Skeleton : public CubePattern
{
public:
    Skeleton(int corners, int edges);

    virtual bool on(const Cube &cube) const;

private:
    int max_unsolved_corners;
    int max_unsolved_edges;
};

#endif
