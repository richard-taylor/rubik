
#include <cassert>
#include <cstring>
#include <iostream>
#include "Cube.h"

typedef unsigned char byte;

/* There are 8 corners with 6 possible orientations and 12 edges with 2
possible orientations.

We can pack this into 14 bytes, but that makes the state hard to manipulate
so we also want to be able to unpack it into one byte per corner and edge.

There may be better ways to pack that are either smaller or easier to
manipulate directly. Since the packing may change in future, do not expose
it outside the private implementation in this file.

Corners

byte 0 : 6 bits of corner-0 plus 2 bits of corner-6
byte 1 : 6 bits of corner-1 plus 2 bits of corner-6
byte 2 : 6 bits of corner-2 plus 2 bits of corner-6
byte 3 : 6 bits of corner-3 plus 2 bits of corner-7
byte 4 : 6 bits of corner-4 plus 2 bits of corner-7
byte 5 : 6 bits of corner-5 plus 2 bits of corner-7

Edges

byte 6  : 4 bits of edge-0-index plus 4 bits of edge-1-index
byte 7  : 4 bits of edge-2-index plus 4 bits of edge-3-index
byte 8  : 4 bits of edge-4-index plus 4 bits of edge-5-index
byte 9  : 4 bits of edge-6-index plus 4 bits of edge-7-index
byte 10 : 4 bits of edge-8-index plus 4 bits of edge-9-index
byte 11 : 4 bits of edge-10-index plus 4 bits of edge-11-index
byte 12 : 1 bit of orientation for edges 0-7
byte 13 : 1 bit of orientation for edges 8-11 plus 4 spare bits.
*/

const byte B0 = 1;
const byte B1 = 2;
const byte B2 = 4;
const byte B3 = 8;
const byte B4 = 16;
const byte B5 = 32;
const byte B6 = 64;
const byte B7 = 128;

const byte B10 = B1 | B0;
const byte B65 = B6 | B5;

const byte B432 = B4 | B3 | B2;
const byte B765 = B7 | B6 | B5;

const byte B3210 = B3 | B2 | B1 | B0;
const byte B7654 = B7 | B6 | B5 | B4; 

void pack(byte *unpacked, byte *packed)
{
    // corners
    
    packed[0] = ((unpacked[0] & B7654) << 1) | ((unpacked[0] & B3210) << 2) | ((unpacked[6] & B65) >> 5);
    packed[1] = ((unpacked[1] & B7654) << 1) | ((unpacked[1] & B3210) << 2) | ((unpacked[6] & B4) >> 3) | ((unpacked[6] & B2) >> 2);
    packed[2] = ((unpacked[2] & B7654) << 1) | ((unpacked[2] & B3210) << 2) | (unpacked[6] & B10);
    
    packed[3] = ((unpacked[3] & B7654) << 1) | ((unpacked[3] & B3210) << 2) | ((unpacked[7] & B65) >> 5);
    packed[4] = ((unpacked[4] & B7654) << 1) | ((unpacked[4] & B3210) << 2) | ((unpacked[7] & B4) >> 3) | ((unpacked[7] & B2) >> 2);
    packed[5] = ((unpacked[5] & B7654) << 1) | ((unpacked[5] & B3210) << 2) | (unpacked[7] & B10);
    
    // edges
    
    packed[6] = (unpacked[8] & B7654) | ((unpacked[9] & B7654) >> 4);
    packed[7] = (unpacked[10] & B7654) | ((unpacked[11] & B7654) >> 4);
    packed[8] = (unpacked[12] & B7654) | ((unpacked[13] & B7654) >> 4);
    packed[9] = (unpacked[14] & B7654) | ((unpacked[15] & B7654) >> 4);
    packed[10] = (unpacked[16] & B7654) | ((unpacked[17] & B7654) >> 4);
    packed[11] = (unpacked[18] & B7654) | ((unpacked[19] & B7654) >> 4);
    
    packed[12] = ((unpacked[8] & B0) << 7) | ((unpacked[9] & B0) << 6) | ((unpacked[10] & B0) << 5) | ((unpacked[11] & B0) << 4) |
                 ((unpacked[12] & B0) << 3) | ((unpacked[13] & B0) << 2) | ((unpacked[14] & B0) << 1) | (unpacked[15] & B0);
               
    packed[13] = ((unpacked[16] & B0) << 7) | ((unpacked[17] & B0) << 6) | ((unpacked[18] & B0) << 5) | ((unpacked[19] & B0) << 4);
}

void unpack(byte *packed, byte *unpacked)
{
    // corners
    // 76543210
    // ...
    //    ...
    //       ..
    
    unpacked[0] = ((packed[0] & B765) >> 1) | ((packed[0] & B432) >> 2);
    unpacked[1] = ((packed[1] & B765) >> 1) | ((packed[1] & B432) >> 2);
    unpacked[2] = ((packed[2] & B765) >> 1) | ((packed[2] & B432) >> 2);
    unpacked[3] = ((packed[3] & B765) >> 1) | ((packed[3] & B432) >> 2);
    unpacked[4] = ((packed[4] & B765) >> 1) | ((packed[4] & B432) >> 2);
    unpacked[5] = ((packed[5] & B765) >> 1) | ((packed[5] & B432) >> 2);
    
    unpacked[6] = ((packed[0] & B10) << 5) | ((packed[1] & B1) << 3) | ((packed[1] & B0) << 2) | (packed[2] & B10);
    unpacked[7] = ((packed[3] & B10) << 5) | ((packed[4] & B1) << 3) | ((packed[4] & B0) << 2) | (packed[5] & B10);
    
    // edges
    // 76543210
    // ....
    //     ....
    
    unpacked[8] = (packed[6] & B7654) | ((packed[12] & B7) >> 7);
    unpacked[9] = ((packed[6] & B3210) << 4) | ((packed[12] & B6) >> 6);
    
    unpacked[10] = (packed[7] & B7654) | ((packed[12] & B5) >> 5);
    unpacked[11] = ((packed[7] & B3210) << 4) | ((packed[12] & B4) >> 4);
    
    unpacked[12] = (packed[8] & B7654) | ((packed[12] & B3) >> 3);
    unpacked[13] = ((packed[8] & B3210) << 4) | ((packed[12] & B2) >> 2);
    
    unpacked[14] = (packed[9] & B7654) | ((packed[12] & B1) >> 1);
    unpacked[15] = ((packed[9] & B3210) << 4) | (packed[12] & B0);
    
    unpacked[16] = (packed[10] & B7654) | ((packed[13] & B7) >> 7);
    unpacked[17] = ((packed[10] & B3210) << 4) | ((packed[13] & B6) >> 6);
    
    unpacked[18] = (packed[11] & B7654) | ((packed[13] & B5) >> 5);
    unpacked[19] = ((packed[11] & B3210) << 4) | ((packed[13] & B4) >> 4);
}

Cube::Twist::Twist(Face face, int turns)
{
    assert(turns > 0 && turns < 4);
    twist = (face << 4) | turns;
}

Cube::Face Cube::Twist::getFace() const
{
    return (Cube::Face)(twist >> 4);
}

int Cube::Twist::getTurns() const
{
    return (twist & 0x03);
}
        
Cube::Twist Cube::Twist::inverse() const
{
    return Cube::Twist(getFace(), 4 - getTurns());
}
        
const byte Cube::SOLVED_STATE[] = {3, 32, 64, 99, 130, 160, 1, 35, 69, 103, 137, 171, 0, 0};

enum Corner { RUF, LUF, LUB, RUB, RDF, LDF, LDB, RDB };
enum Edge { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB };

enum Axis { X, Y, Z };
enum Orient { XYZ, XZY, YXZ, YZX, ZXY, ZYX };

byte rotations[3][6] = { { XZY, XYZ, ZXY, ZYX, YXZ, YZX },
                         { ZYX, ZXY, YZX, YXZ, XZY, XYZ },
                         { YXZ, YZX, XYZ, XZY, ZYX, ZXY } };

const char *CornerName[] = { "RUF", "LUF", "LUB", "RUB", "RDF", "LDF", "LDB", "RDB" };
const char *EdgeName[] = { "RU", "UF", "LU", "UB", "RF", "LF", "LB", "RB", "RD", "DF", "LD", "DB" };
const char *OrientName[] = { "XYZ", "XZY", "YXZ", "YZX", "ZXY", "ZYX" };
const char *FlipName[] = { "Good", "Bad" };

Cube::Cube()
{
    // pre-calculate the packed SOLVED_STATE
    // byte unpacked[] = {0, 1<<4, 2<<4, 3<<4, 4<<4, 5<<4, 6<<4, 7<<4, 0, 1<<4, 2<<4, 3<<4, 4<<4, 5<<4, 6<<4, 7<<4, 8<<4, 9<<4, 10<<4, 11<<4};
    // pack(unpacked, state);
    // debug("solved state");

    memcpy(state, SOLVED_STATE, STATE_SIZE);
}

bool Cube::solved() const
{
    return (memcmp(state, SOLVED_STATE, STATE_SIZE) == 0);
}

static inline byte hi4(byte hi_lo)
{
    return (hi_lo >> 4);
}

static inline byte lo4(byte hi_lo)
{
    return (hi_lo & 0x0f);
}

static inline byte flip_lsb(byte hi_lo)
{
    return (hi_lo ^ 0x01);
}

static inline byte get_corner(Corner corner, byte *unpacked)
{
    return unpacked[corner];
}

static inline void set_corner(Corner corner, byte index, byte orient, byte *unpacked)
{
    unpacked[corner] = (index << 4) | orient;
}

static void corner_cycle(Axis axis, byte* unpacked, Corner a, Corner b, Corner c, Corner d)
{
    // a -> b -> c -> d -> a
    
    byte A = get_corner(a, unpacked);
    byte B = get_corner(b, unpacked);
    byte C = get_corner(c, unpacked);
    byte D = get_corner(d, unpacked);
    
    byte *table = rotations[axis];
    
    set_corner(b, hi4(A), table[lo4(A)], unpacked);
    set_corner(c, hi4(B), table[lo4(B)], unpacked);
    set_corner(d, hi4(C), table[lo4(C)], unpacked);
    set_corner(a, hi4(D), table[lo4(D)], unpacked);
}

static void corner_swap(byte *unpacked, Corner a, Corner b)
{
    byte A = get_corner(a, unpacked);
    byte B = get_corner(b, unpacked);
    
    set_corner(b, hi4(A), lo4(A), unpacked);
    set_corner(a, hi4(B), lo4(B), unpacked);
}

static inline byte get_edge(Edge edge, byte *unpacked)
{
    return unpacked[edge + 8];
}

static inline void set_edge(Edge edge, byte index, byte orient, byte *unpacked)
{
    unpacked[edge + 8] = (index << 4) | orient;
}

static void edge_cycle(Axis axis, byte *unpacked, Edge a, Edge b, Edge c, Edge d)
{
    // a -> b -> c -> d -> a
    
    byte A = get_edge(a, unpacked);
    byte B = get_edge(b, unpacked);
    byte C = get_edge(c, unpacked);
    byte D = get_edge(d, unpacked);
    
    if (axis == Z)
    {
        set_edge(b, hi4(A), flip_lsb(lo4(A)), unpacked);
        set_edge(c, hi4(B), flip_lsb(lo4(B)), unpacked);
        set_edge(d, hi4(C), flip_lsb(lo4(C)), unpacked);
        set_edge(a, hi4(D), flip_lsb(lo4(D)), unpacked);
    }
    else
    {
        set_edge(b, hi4(A), lo4(A), unpacked);
        set_edge(c, hi4(B), lo4(B), unpacked);
        set_edge(d, hi4(C), lo4(C), unpacked);
        set_edge(a, hi4(D), lo4(D), unpacked);
    }
}

static void edge_swap(byte *unpacked, Edge a, Edge b)
{
    byte A = get_edge(a, unpacked);
    byte B = get_edge(b, unpacked);
    
    set_edge(b, hi4(A), lo4(A), unpacked);
    set_edge(a, hi4(B), lo4(B), unpacked);
}

void Cube::twist(Twist turn)
{
    // debug("before twist");
    
    Face face = turn.getFace();
    int turns = turn.getTurns();
    
    byte unpacked[20];
    unpack(state, unpacked);
    
    switch (face)
    {
        case L:
            switch (turns) {
                case 1:
                    corner_cycle(X, unpacked, LUB, LUF, LDF, LDB);
                    edge_cycle(X, unpacked, LU, LF, LD, LB);
                    break;
                case 2:
                    corner_swap(unpacked, LUB, LDF);
                    corner_swap(unpacked, LUF, LDB);
                    edge_swap(unpacked, LU, LD);
                    edge_swap(unpacked, LF, LB);
                    break;
                case 3:
                    corner_cycle(X, unpacked, LDB, LDF, LUF, LUB);
                    edge_cycle(X, unpacked, LB, LD, LF, LU);
                    break;
            }
            break;
            
        case R:
            switch (turns) {
                case 1:
                    corner_cycle(X, unpacked, RUF, RUB, RDB, RDF);
                    edge_cycle(X, unpacked, RU, RB, RD, RF);
                    break;
                case 2:
                    corner_swap(unpacked, RUF, RDB);
                    corner_swap(unpacked, RUB, RDF);
                    edge_swap(unpacked, RU, RD);
                    edge_swap(unpacked, RF, RB);
                    break;
                case 3:
                    corner_cycle(X, unpacked, RDF, RDB, RUB, RUF);
                    edge_cycle(X, unpacked, RF, RD, RB, RU);
                    break;
            }
            break;
            
        case U:
            switch (turns) {
                case 1:
                    corner_cycle(Y, unpacked, LUF, LUB, RUB, RUF);
                    edge_cycle(Y, unpacked, LU, UB, RU, UF);
                    break;
                case 2:
                    corner_swap(unpacked, LUF, RUB);
                    corner_swap(unpacked, LUB, RUF);
                    edge_swap(unpacked, LU, RU);
                    edge_swap(unpacked, UF, UB);
                    break;
                case 3:
                    corner_cycle(Y, unpacked, RUF, RUB, LUB, LUF);
                    edge_cycle(Y, unpacked, UF, RU, UB, LU);
                    break;
            }
            break;
            
        case D:
            switch (turns) {
                case 1:
                    corner_cycle(Y, unpacked, LDF, RDF, RDB, LDB);
                    edge_cycle(Y, unpacked, DF, RD, DB, LD);
                    break;
                case 2:
                    corner_swap(unpacked, LDF, RDB);
                    corner_swap(unpacked, LDB, RDF);
                    edge_swap(unpacked, DF, DB);
                    edge_swap(unpacked, LD, RD);
                    break;
                case 3:
                    corner_cycle(Y, unpacked, LDB, RDB, RDF, LDF);
                    edge_cycle(Y, unpacked, LD, DB, RD, DF);
                    break;
            }
            break;
            
        case F:
            switch (turns) {
                case 1:
                    corner_cycle(Z, unpacked, LUF, RUF, RDF, LDF);
                    edge_cycle(Z, unpacked, LF, UF, RF, DF);
                    break;
                case 2:
                    corner_swap(unpacked, LUF, RDF);
                    corner_swap(unpacked, LDF, RUF);
                    edge_swap(unpacked, LF, RF);
                    edge_swap(unpacked, UF, DF);
                    break;
                case 3:
                    corner_cycle(Z, unpacked, LDF, RDF, RUF, LUF);
                    edge_cycle(Z, unpacked, DF, RF, UF, LF);
                    break;
            }
            break;
            
        case B:
            switch (turns) {
                case 1:
                    corner_cycle(Z, unpacked, RUB, LUB, LDB, RDB);
                    edge_cycle(Z, unpacked, RB, UB, LB, DB);
                    break;
                case 2:
                    corner_swap(unpacked, LDB, RUB);
                    corner_swap(unpacked, LUB, RDB);
                    edge_swap(unpacked, LB, RB);
                    edge_swap(unpacked, UB, DB);
                    break;
                case 3:
                    corner_cycle(Z, unpacked, RDB, LDB, LUB, RUB);
                    edge_cycle(Z, unpacked, DB, LB, UB, RB);
                    break;
            }
            break;
    }
    pack(unpacked, state);
    // debug("after twist");
}

bool Cube::operator==(const Cube &other) const
{
    return (memcmp(state, other.state, STATE_SIZE) == 0);
}

bool Cube::operator!=(const Cube &other) const
{
    return (memcmp(state, other.state, STATE_SIZE) != 0);
}

bool Cube::operator<(const Cube &other) const
{
    return (memcmp(state, other.state, STATE_SIZE) < 0);
}

unsigned long long Cube::corner_bits() const
{
    return ((unsigned long long)state[0] << 40) |
           ((unsigned long long)state[1] << 32) |
           ((unsigned long long)state[2] << 24) |
           ((unsigned long long)state[3] << 16) | 
           ((unsigned long long)state[4] <<  8) | 
           ((unsigned long long)state[5]);
}

void Cube::debug(const char *label)
{
    std::cout << label << std::endl;
    
    std::cout << "    packed state =";
    for (int i = 0; i < STATE_SIZE; i++)
        std::cout << " " << int(state[i]);
    std::cout << std::endl;
    
    byte unpacked[20];
    unpack(state, unpacked);
    
    std::cout << "    corners" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        byte index = hi4(unpacked[i]);
        byte orient = lo4(unpacked[i]);
        
        std::cout << "      " << CornerName[i] << " <- " << CornerName[index] << " " << OrientName[orient] << std::endl;
    }
    
    std::cout << "    edges" << std::endl;
    for (int i = 0; i < 12; i++)
    {
        byte index = hi4(unpacked[8 + i]);
        byte orient = lo4(unpacked[8 + i]);
        
        std::cout << "      " << EdgeName[i] << " <- " << EdgeName[index] << " " << FlipName[orient] << std::endl;
    }
}
