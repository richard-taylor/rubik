
#include <stdexcept>
#include "Cube.h"
#include "Skeleton.h"

Skeleton::Skeleton(int corners, int edges)
{
    max_unsolved_corners = corners;
    max_unsolved_edges = edges;
}

bool Skeleton::on(const Cube &cube) const
{
    int badCorners = 0;
    for (int i = 0; i < 8; i++)
    {
        if (!cube.cornerSolved(CornerSlot(i)))
            badCorners++;
    }
    if (badCorners > max_unsolved_corners)
        return false;

    int badEdges = 0;
    for (int i = 0; i < 12; i++)
    {
        if (!cube.edgeSolved(EdgeSlot(i)))
            badEdges++;
    }
    return badEdges <= max_unsolved_edges;
}
