
#ifndef FINISHED_H
#define FINISHED_H

#include "CubePattern.h"

/**
Class to represent a solved cube.

This is the simplest possible cube pattern.
*/
class Finished : public CubePattern
{
public:
    virtual bool on(const Cube &cube) const;
};

#endif
