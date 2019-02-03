
#ifndef EDGE_H
#define EDGE_H

#include "Enums.h"
#include "Typedefs.h"

/**
Class to represent an edge piece in a cube.

There are 12 edges with 8 possible orientations.

For any axis an edge is either oriented or unoriented with respect to that
axis. So we could choose one axis as a reference and then just store a single
boolean orientation. But then it would be harder to work out which edges are
oriented with respect to the other axes if we wanted to. So here we keep all
three axes.

When an edge is rotated by 90 degrees about an axis its orientation flips with
respect to that axis, whether the rotation is clockwise or anticlockwise.

When an edge is rotated by 180 degrees about an axis its orientation does
not change.
*/
class Edge
{
public:
    enum Orientation { OOO, UOO, OUO, UUO, OOU, UOU, OUU, UUU };

    Edge() { /* for uninitilised arrays */ }

    Edge(int index, Orientation orientation = OOO);

    int getIndex() const;
    Orientation getOrientation() const;

    Edge rotate90(Axis axis) const;
    bool operator==(const Edge &other) const;

private:
    byte edge;
};

const Edge RU(0);
const Edge UF(1);
const Edge LU(2);
const Edge UB(3);
const Edge RF(4);
const Edge LF(5);
const Edge LB(6);
const Edge RB(7);
const Edge RD(8);
const Edge DF(9);
const Edge LD(10);
const Edge DB(11);

#endif
