
#ifndef ITERATIVEDEEPENING_H
#define ITERATIVEDEEPENING_H

#include <string>
#include "Cube.h"
#include "CubeCache.h"
#include "Scramble.h"

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
    Scramble solve(const Cube &cube) const;
    
    /**
    God's number.
    */
    static const int MAX_MOVES = 20;
    
private:
    const CubeCache *m_cubes;
    CubeCache *corners;
    
    Scramble try_depth(int depth, const Cube &cube) const;
    bool can_solve_in_less(int moves, const Cube &cube) const;
};

#endif
