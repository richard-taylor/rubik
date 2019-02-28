
#ifndef FINISHED_H
#define FINISHED_H

#include <unordered_map>
#include "CubeHash.h"
#include "CubePattern.h"

/**
Class to represent a solved cube.

This is the simplest possible cube pattern.
*/
class Finished : public CubePattern
{
public:
    Finished(int cache_depth);

    virtual bool on(const Cube &cube) const;

    virtual bool search(const Cube &cube,
                        const Sequence &twists,
                        std::vector<Sequence> &results) const;

private:
    std::unordered_map<Cube, std::vector<Sequence>> cache;

    void cacheDepth(int depth);
};

#endif
