
#include <stdexcept>
#include "TwoCornersTwoEdges.h"
#include "Cube.h"

bool TwoCornersTwoEdges::on(const Cube &cube) const
{
    int badCorners = 0;
    for (int i = 0; i < 8; i++)
    {
        if (!cube.cornerSolved(CornerSlot(i)))
            badCorners++;
    }
    if (badCorners != 2)
        return false;

    int badEdges = 0;
    for (int i = 0; i < 12; i++)
    {
        if (!cube.edgeSolved(EdgeSlot(i)))
            badEdges++;
    }
    return badEdges == 2;
}
