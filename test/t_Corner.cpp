
#include <cassert>
#include "Corner.h"

int main()
{
    // Default orientation is XYZ
    Corner corner(0);
    assert(corner.getOrientation() == Corner::XYZ);

    // Getters
    Corner corner7(7, Corner::ZYX);
    assert(corner7.getIndex() == 7);
    assert(corner7.getOrientation() == Corner::ZYX);

    // Rotation by 90 degrees changes the orientation
    Corner corner90 = corner.rotate90(X);
    assert(corner90.getIndex() == 0);
    assert(corner90.getOrientation() == Corner::XZY);

    // Rotation by another 90 degrees restores the orientation
    Corner corner180 = corner90.rotate90(X);
    assert(corner180.getIndex() == 0);
    assert(corner180.getOrientation() == Corner::XYZ);

    assert(corner180 == corner);

    // An array of solved corners
    Corner solved[] = { RUF, LUF, LUB ,RUB, RDF, LDF, LDB, RDB };
    for (int i = 0; i < 8; i++)
    {
        assert(solved[i].getIndex() == i);
        assert(solved[i].getOrientation() == Corner::XYZ);
    }

    // An uninitialised array
    Corner array[8];
    for (int i = 0; i < 8; i++)
    {
        array[i] = Corner(i);
    }
}
