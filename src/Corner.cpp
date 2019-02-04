
#include <cassert>
#include "Corner.h"

Corner::Corner(int index, Corner::Orientation orientation)
{
    assert(index >= 0 && index <= 7);
    corner = index | (orientation << 4);
}

int Corner::getIndex() const
{
    return (corner & 0x0f);
}

Corner::Orientation Corner::getOrientation() const
{
    return (Corner::Orientation)(corner >> 4);
}

// Look up table to map current orientation to new orientation when rotated
// about each axis. The first array dimension is the axis (x, y, z) and the
// second array dimension is the current orientation.
//
static Corner::Orientation rotations[3][6] = {

{Corner::XZY,Corner::XYZ,Corner::ZXY,Corner::ZYX,Corner::YXZ,Corner::YZX},
{Corner::ZYX,Corner::ZXY,Corner::YZX,Corner::YXZ,Corner::XZY,Corner::XYZ},
{Corner::YXZ,Corner::YZX,Corner::XYZ,Corner::XZY,Corner::ZYX,Corner::ZXY}

};

Corner Corner::rotate90(Axis axis) const
{
    return Corner(getIndex(), rotations[axis][getOrientation()]);
}

bool Corner::operator==(const Corner &other) const
{
    return (corner == other.corner);
}
