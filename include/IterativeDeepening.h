
#ifndef ITERATIVEDEEPENING_H
#define ITERATIVEDEEPENING_H

#include <string>
#include "Cube.h"
#include "CubeCache.h"
#include "Sequence.h"

class IterativeDeepening
{
public:
    /**
    */
    IterativeDeepening();

    /**
    */
    void set_position_cache(const CubeCache &positions);

    /**
    */
    void set_orientation_cache(const CubeCache &orientations);

    /**
    */
    Sequence solve(const Cube &cube) const;

    /**
    God's number.
    */
    static const int MAX_MOVES = 20;

private:
    const CubeCache *m_cubes;
    const CubeCache *m_orients;

    Sequence try_depth(int depth, const Cube &cube) const;
    bool can_solve_in_less(int moves, const Cube &cube) const;
};

#endif
