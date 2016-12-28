
#include "CornersCacheLayer.h"

// Each "corner state" can be stored as 7 bytes.
//
// That is one byte per corner. We only need to store 7 of the 8 corners,
// since the state of the 8th is completely determined by the other 7.

CornersCacheLayer::CornersCacheLayer(const std::string &basename, int depth)
: CacheLayer(basename, depth, 7)
{
}

void CornersCacheLayer::extract_state(const Cube &cube, unsigned char *state) const
{
    unsigned char corners[8];
    unsigned char edges[12];
    
    cube.get_pieces(corners, edges); // TODO a separate get_edges method?
        
    state[0] = corners[0];
    state[1] = corners[1];
    state[2] = corners[2];
    state[3] = corners[3];
    state[4] = corners[4];
    state[5] = corners[5];
    state[6] = corners[6];
}
