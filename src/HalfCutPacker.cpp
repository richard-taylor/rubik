
#include <iostream>
#include "HalfCutPacker.h"
#include "Cube.h"
#include "State.h"

/*
A sub-problem which captures the approximate position of the pieces. For
each piece we capture whether it is in the right "half" of the cube.

For corners: is the corner in the correct slot or one of the three
adjacent slots connected by one edge. (1 bit per corner)

For edges: is the edge in the correct slot or one of the six slots on 
the two intersecting faces. (1 bit per edge)

We only actually need 7 corners to determine the position of the 8th.
We also only need 11 edges to determine the position of the 12th. 

(maybe add orientation bits too?)
*/

const byte B0 = 1;
const byte B1 = 2;
const byte B2 = 4;
const byte B3 = 8;
const byte B4 = 16;
const byte B5 = 32;
const byte B6 = 64;
const byte B7 = 128;

const byte B7654 = B7 | B6 | B5 | B4;

int HalfCutPacker::state_bits()
{
    return 18; // 7 * 1 + 11 * 1
}

inline byte co(byte corner, byte i1, byte i2, byte i3, byte i4)
{
    byte i = ((corner & B7654) >> 4);
    return (i == i1) || (i == i2) || (i == i3) || (i == i4) ? 1 : 0;
}

inline byte ed(byte edge, byte index)
{
    return ((edge & B7654) >> 4) == index ? 1 : 0;
}

void HalfCutPacker::pack(const Cube &cube, State &state)
{
    byte corners[8];
    byte edges[12];
    
    cube.get_pieces(corners, edges);
    
    byte c1 = co(corners[Cube::LUF], Cube::LUF, Cube::LDF, Cube::LUB, Cube::RUF);
    byte c2 = co(corners[Cube::RUF], Cube::RUF, Cube::RDF, Cube::RUB, Cube::LUF);
    byte c3 = co(corners[Cube::LUB], Cube::LUB, Cube::LDB, Cube::LUF, Cube::RUB);
    byte c4 = co(corners[Cube::RUB], Cube::RUB, Cube::RDB, Cube::RUF, Cube::LUB);
    byte c5 = co(corners[Cube::LDF], Cube::LDF, Cube::LUF, Cube::LDB, Cube::RDF);
    byte c6 = co(corners[Cube::RDF], Cube::RDF, Cube::RUF, Cube::RDB, Cube::LDF);
    byte c7 = co(corners[Cube::LDB], Cube::LDB, Cube::LUB, Cube::LDF, Cube::RDB);
    
    byte e1 = ed(edges[0], 0);
    byte e2 = ed(edges[1], 1);
    byte e3 = ed(edges[2], 2);
    byte e4 = ed(edges[3], 3);
    byte e5 = ed(edges[4], 4);
    byte e6 = ed(edges[5], 5);
    byte e7 = ed(edges[6], 6);
    byte e8 = ed(edges[7], 7);
    byte e9 = ed(edges[8], 8);
    byte e10 = ed(edges[9], 9);
    byte e11 = ed(edges[10], 10);
    
    state.set_byte(0, (c1 << 7) | (c2 << 6) | (c3 << 5) | (c4 << 4) | (c5 << 3) | (c6 << 2) | (c7 << 1) | e1);
    state.set_byte(1, (e2 << 7) | (e3 << 6) | (e4 << 5) | (e5 << 4) | (e6 << 3) | (e7 << 2) | (e8 << 1) | e9);
    state.set_byte(2, (e10 << 1) | e11);
}
