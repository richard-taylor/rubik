
#ifndef CUBEPATTERN_H
#define CUBEPATTERN_H

#include <vector>
#include "Cube.h"
#include "Sequence.h"

/**
Class to represent a general arrangement of a cube.

A cube has many states, not just solved and unsolved. This class is an
interface to test for a general pattern, such as "one face solved"
or "all corners solved".
*/
class CubePattern
{
public:
    /**
    Does the pattern appear on the given cube?
    */
    virtual bool on(const Cube &cube) const = 0;

    /**
    Can the pattern be found "near" the given cube, which has been reached
    by the sequence "twists"?

    This is intended to be overriden by classes which cache cube positions
    to reduce the search depth. For those classes they may need to return
    more than one result by appending multiple extensions of "twists" onto
    the "results".

    The default behaviour for normal patterns is to simply add "twists"
    to "results" if on(cube) is true.
    */
    virtual bool search(const Cube &cube,
                        const Sequence &twists,
                        std::vector<Sequence> &results) const;
};

#endif
