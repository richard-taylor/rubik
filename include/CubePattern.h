
#ifndef CUBEPATTERN_H
#define CUBEPATTERN_H

class Cube;

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
};

#endif
