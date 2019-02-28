
#include <cassert>
#include "Edge.h"

Edge::Edge(int index, Edge::Orientation orientation)
{
    assert(index >= 0 && index <= 11);
    edge = index | (orientation << 4);
}

int Edge::getIndex() const
{
    return (edge & 0x0f);
}

Edge::Orientation Edge::getOrientation() const
{
    return (Edge::Orientation)(edge >> 4);
}

// Look up table to map current orientation to new orientation when rotated
// about each axis. The first array dimension is the axis (x, y, z) and the
// second array dimension is the current orientation.
//
static Edge::Orientation rotations[3][8] = {

{Edge::UOO,Edge::OOO,Edge::UUO,Edge::OUO,Edge::UOU,Edge::OOU,Edge::UUU,Edge::OUU},
{Edge::OUO,Edge::UUO,Edge::OOO,Edge::UOO,Edge::OUU,Edge::UUU,Edge::OOU,Edge::UOU},
{Edge::OOU,Edge::UOU,Edge::OUU,Edge::UUU,Edge::OOO,Edge::UOO,Edge::OUO,Edge::UUO}

};

Edge Edge::rotate90(Axis axis) const
{
    return Edge(getIndex(), rotations[axis][getOrientation()]);
}

bool Edge::operator==(const Edge &other) const
{
    return (edge == other.edge);
}

bool Edge::operator<(const Edge &other) const
{
    return (edge < other.edge);
}

std::size_t Edge::hash() const
{
    return edge;
}
