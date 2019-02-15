
#ifndef CUBE_H
#define CUBE_H

#include <set>
#include "Corner.h"
#include "Edge.h"
#include "Twist.h"

class Cube
{
public:
    /**
    Create a solved cube.
    */
    Cube();

    /**
    Test whether the cube is solved.
    */
    bool solved() const;

    /**
    Make a single move (in outer-block metric terms).
    */
    void twist(Twist turn);

    /**
    Test for cubes with equal positions.
    */
    bool operator==(const Cube &other) const;

    /**
    Test for cubes with different positions.
    */
    bool operator!=(const Cube &other) const;

    /**
    Test for cube ordering (used by std::set)
    */
    bool operator<(const Cube &other) const;

    /**
    Is a particular corner solved?
    */
    bool cornerSolved(CornerSlot slot) const;

    /**
    Which corner is currently in a particular corner slot?
    */
    Corner cornerSlot(CornerSlot slot) const;

    /**
    Is a particular edge solved?
    */
    bool edgeSolved(EdgeSlot slot) const;

    /**
    Which edge is currently in a particular edge slot?
    */
    Edge edgeSlot(EdgeSlot slot) const;

    /**
    Return a randomised cube.

    All valid cube states should be equally likely.
    */
    Cube randomise() const;

    /**
    Return a randomised cube, but leaving some corners and/or edges unchanged.

    All valid cube states should be equally likely.
    */
    Cube randomise(const std::set<CornerSlot> &fixedCorners,
                   const std::set<EdgeSlot> &fixedEdges) const;

private:
    Corner corners[8];
    Edge edges[12];

    void cornerCycle(Axis axis, CornerSlot a, CornerSlot b, CornerSlot c, CornerSlot d);
    void cornerSwap(CornerSlot a, CornerSlot b);

    void cornerExchange(CornerSlot a, CornerSlot b);
    void cornerTwist(CornerSlot a, int times);

    void edgeCycle(Axis axis, EdgeSlot a, EdgeSlot b, EdgeSlot c, EdgeSlot d);
    void edgeSwap(EdgeSlot a, EdgeSlot b);

    void edgeExchange(EdgeSlot a, EdgeSlot b);
    void edgeFlip(EdgeSlot a);
};

#endif
