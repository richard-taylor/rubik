
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

    /**
    Set a face to only allow double moves - e.g. R2 only and not R or R'

    This is often used in conjunction with Domino Reduction.
    */
    void only_allow_doubles(Face face);

private:
    std::vector<Sequence> try_depth(int depth,
                                    bool firstOnly,
                                    const Cube &cube,
                                    const CubePattern& pattern) const;
    bool all_turns_allowed;
    bool turn_allowed[6][3];
};

#endif
