
#ifndef CUBE_H
#define CUBE_H

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

private:
    Corner corners[8];
    Edge edges[12];

    void cornerCycle(Axis axis, Corner a, Corner b, Corner c, Corner d);
    void cornerSwap(Corner a, Corner b);

    void edgeCycle(Axis axis, Edge a, Edge b, Edge c, Edge d);
    void edgeSwap(Edge a, Edge b);
};

#endif
