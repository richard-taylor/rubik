
#ifndef CORNERSCACHELAYER_H
#define CORNERSCACHELAYER_H

#include "CacheLayer.h"
#include "Cube.h"

// implements LayerType for use in a Cache

// This cache holds the state of all the cube's corners.
// The maximum number of turns needed to solve just the corners is 11.

class CornersCacheLayer : public CacheLayer
{
public:
    /**
    Load a layer of a certain depth (number of moves from solved).
    */
    CornersCacheLayer(const std::string &basename, int deep);
  
protected:
    void extract_state(const Cube &cube, unsigned char *state) const;
};

#endif
