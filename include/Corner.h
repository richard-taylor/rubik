
#ifndef CORNER_H
#define CORNER_H

#include "Enums.h"
#include "Typedefs.h"

/**
Class to represent a corner piece in a cube.

There are 8 corners with 6 possible orientations.

The orientations confused me for a while, since a corner in a given position
can only have 3 different orientations. But across all the possible positions
there are actually 6 different orientations.

When a corner is rotated by 90 degrees about an axis its orientation changes,
but the change is the same whether the rotation is clockwise or anticlockwise.

When a corner is rotated by 180 degrees about an axis its orientation does
not change.
*/
class Corner
{
public:
    enum Orientation { XYZ, XZY, YXZ, YZX, ZXY, ZYX };

    Corner() { /* for uninitilised arrays */ }

    Corner(int index, Orientation orientation = XYZ);

    int getIndex() const;
    Orientation getOrientation() const;

    Corner rotate90(Axis axis) const;

    bool operator==(const Corner &other) const;
    bool operator<(const Corner &other) const;

    std::size_t hash() const;

private:
    byte corner;
};

#endif
