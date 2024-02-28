
#include <stdexcept>
#include "ThreeCornersThreeEdges.h"
#include "Cube.h"

bool ThreeCornersThreeEdges::on(const Cube &cube) const
{
    int badCorners = 0;
    for (int i = 0; i < 8; i++)
    {
        if (!cube.cornerSolved(CornerSlot(i)))
            badCorners++;
    }
    if (badCorners != 3)
        return false;

    int badEdges = 0;
    for (int i = 0; i < 12; i++)
    {
        if (!cube.edgeSolved(EdgeSlot(i)))
            badEdges++;
    }
    return badEdges == 3;
}
