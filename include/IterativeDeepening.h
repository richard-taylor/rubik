
#ifndef ITERATIVEDEEPENING_H
#define ITERATIVEDEEPENING_H

#include <vector>
#include "Cube.h"
#include "Sequence.h"

class CubePattern;

class IterativeDeepening
{
public:
    IterativeDeepening();

    /**
    Return any optimal solution to the pattern on the cube.
    */
    Sequence solve(const Cube &cube, const CubePattern& pattern) const;

    /**
    Return all optimal solutions to the pattern on the cube.
    */
    std::vector<Sequence> allSolutions(const Cube &cube,
                                       const CubePattern& pattern) const;
    /**
    God's number.
    */
    static const int MAX_MOVES = 20;

private:
    std::vector<Sequence> try_depth(int depth,
                                    bool firstOnly,
                                    const Cube &cube,
                                    const CubePattern& pattern) const;
};

#endif
