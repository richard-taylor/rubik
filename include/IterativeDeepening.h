
#ifndef ITERATIVEDEEPENING_H
#define ITERATIVEDEEPENING_H

#include "Cube.h"
#include "Sequence.h"

class CubePattern;

class IterativeDeepening
{
public:
    IterativeDeepening();

    Sequence solve(const Cube &cube, const CubePattern& pattern) const;

    /**
    God's number.
    */
    static const int MAX_MOVES = 20;

private:
    Sequence try_depth(int depth,
                       const Cube &cube,
                       const CubePattern& pattern) const;
};

#endif
