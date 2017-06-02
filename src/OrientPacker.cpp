
#include "OrientPacker.h"
#include "Cube.h"
#include "State.h"

/*
A sub-problem which just captures the orientation of each piece
without its position.

We only need 7 corners and 11 edges because the last of each
is fixed by knowledge of the others.
*/

const byte B0 = 1;
const byte B1 = 2;
const byte B2 = 4;
const byte B3 = 8;
const byte B4 = 16;
const byte B5 = 32;
const byte B6 = 64;
const byte B7 = 128;

const byte B210 = B2 | B1 | B0;

int OrientPacker::state_bits()
{
    return 32; // 7 * 3 + 11 * 1
}

inline byte ccee(byte corner1, byte corner2, byte edge1, byte edge2)
{
    return ((corner1 & B210) << 5) | ((corner2 & B210) << 2) |
           ((edge1 & B0) << 1) | (edge2 & B0);
}

void OrientPacker::pack(const Cube &cube, State &state)
{
    byte corners[8];
    byte edges[12];
    
    cube.get_pieces(corners, edges);
    
    state.set_byte(0, ccee(corners[0], corners[1], edges[0], edges[1]));
    state.set_byte(1, ccee(corners[2], corners[3], edges[2], edges[3]));
    state.set_byte(2, ccee(corners[4], corners[5], edges[4], edges[5]));
            
    state.set_byte(3, ((corners[6] & B210) << 5) | ((edges[6] & B0) << 4) | 
                                                   ((edges[7] & B0) << 3) |
                                                   ((edges[8] & B0) << 2) |
                                                   ((edges[9] & B0) << 1) |
                                                   (edges[10] & B0));
}
