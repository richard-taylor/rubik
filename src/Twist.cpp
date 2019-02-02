
#include <cassert>
#include <cstring>
#include <iostream>
#include "Twist.h"

Twist::Twist()
{
    twist = 0;
}

Twist::Twist(Face face, int turns)
{
    assert(turns > 0 && turns < 4);
    twist = (face << 4) | turns;
}

Face Twist::getFace() const
{
    return (Face)(twist >> 4);
}

int Twist::getTurns() const
{
    return (twist & 0x03);
}

Twist Twist::inverse() const
{
    return Twist(getFace(), 4 - getTurns());
}

bool Twist::operator==(const Twist &other) const
{
    return (twist == other.twist);
}
