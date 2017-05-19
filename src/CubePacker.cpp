
#include "CubePacker.h"
#include "Cube.h"
#include "State.h"

/*

There are 8 corners with 6 possible orientations and 12 edges with 2
possible orientations. So that is 6 bits per corner and 5 bits per edge.

But if 7 corners are known the last corner can only have one possible value.
And if 11 edges are known the last edge also only has one option.

Therefore the cube state can be packed into 7 * 6 bits for the corners
plus 11 * 5 bits for the edges. Which is 97 bits.

There may be better ways to pack that are smaller, but this straightforward
way will do for now.

byte 0 : 6 bits of corner-0 plus edge-0 orientation and edge-1 orientation
byte 1 : 6 bits of corner-1 plus edge-2 orientation and edge-3 orientation
byte 2 : 6 bits of corner-2 plus edge-4 orientation and edge-5 orientation
byte 3 : 6 bits of corner-3 plus edge-6 orientation and edge-7 orientation
byte 4 : 6 bits of corner-4 plus edge-8 orientation and edge-9 orientation
byte 5 : 6 bits of corner-5 plus 2 bits of edge-10 index
byte 6 : 6 bits of corner-6 plus 2 bits of edge-10 index

byte 7  : 4 bits of edge-0 index plus 4 bits of edge-1-index
byte 8  : 4 bits of edge-2 index plus 4 bits of edge-3-index
byte 9  : 4 bits of edge-4 index plus 4 bits of edge-5-index
byte 10 : 4 bits of edge-6 index plus 4 bits of edge-7-index
byte 11 : 4 bits of edge-8 index plus 4 bits of edge-9-index

byte 12 : 1 bit of edge-10 orientation

*/

const byte B0 = 1;
const byte B1 = 2;
const byte B2 = 4;
const byte B3 = 8;
const byte B4 = 16;
const byte B5 = 32;
const byte B6 = 64;
const byte B7 = 128;

const byte B76 = B7 | B6;
const byte B54 = B5 | B4;

const byte B3210 = B3 | B2 | B1 | B0;
const byte B7654 = B7 | B6 | B5 | B4; 

int CubePacker::state_bits()
{
    return 97;
}

inline byte cio(byte corner)    // corner index + orientation
{
    return ((corner & B7654) << 1) | ((corner & B3210) << 2);
}

inline byte ei(byte edge1, byte edge2)    // pair of edge indices
{
    return (edge1 & B7654) | ((edge2 & B7654) >> 4);
}

inline byte eo(byte edge1, byte edge2)    // pair of edge orientations
{
    return ((edge1 & B0) << 1) | (edge2 & B0);
}

void CubePacker::pack(const Cube &cube, State &state)
{
    byte corners[8];
    byte edges[12];
    
    cube.get_pieces(corners, edges);
    
    state.set_byte(0, cio(corners[0]) | eo(edges[0], edges[1]));
    state.set_byte(1, cio(corners[1]) | eo(edges[2], edges[3]));
    state.set_byte(2, cio(corners[2]) | eo(edges[4], edges[5]));
    state.set_byte(3, cio(corners[3]) | eo(edges[6], edges[7]));
    state.set_byte(4, cio(corners[4]) | eo(edges[8], edges[9]));
    
    state.set_byte(5, cio(corners[5]) | ((edges[10] & B76) >> 6));
    state.set_byte(6, cio(corners[6]) | ((edges[10] & B54) >> 4));
                   
    state.set_byte(7, ei(edges[0], edges[1]));
    state.set_byte(8, ei(edges[2], edges[3]));
    state.set_byte(9, ei(edges[4], edges[5]));
    state.set_byte(10, ei(edges[6], edges[7]));
    state.set_byte(11, ei(edges[8], edges[9]));
    
    state.set_byte(12, edges[10] & B0);
}
