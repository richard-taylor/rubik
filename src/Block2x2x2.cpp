
#include <stdexcept>
#include "Block2x2x2.h"
#include "Cube.h"

static inline bool block(const Cube &cube,
                         CornerSlot c, EdgeSlot e1, EdgeSlot e2, EdgeSlot e3)
{
    return cube.cornerSolved(c) &&
           cube.edgeSolved(e1) &&
           cube.edgeSolved(e2) &&
           cube.edgeSolved(e3);
}

bool Block2x2x2::on(const Cube &cube) const
{
    return block(cube, RUF, RU, UF, RF) ||
           block(cube, LUF, LU, UF, LF) ||
           block(cube, LUB, LU, UB, LB) ||
           block(cube, RUB, RU, UB, RB) ||
           block(cube, RDF, RD, DF, RF) ||
           block(cube, LDF, LD, DF, LF) ||
           block(cube, LDB, LD, DB, LB) ||
           block(cube, RDB, RD, DB, RB);
}

CornerSlot Block2x2x2::fixedCorner(const Cube &cube) const
{
    if (block(cube, RUF, RU, UF, RF)) return RUF;
    if (block(cube, LUF, LU, UF, LF)) return LUF;
    if (block(cube, LUB, LU, UB, LB)) return LUB;
    if (block(cube, RUB, RU, UB, RB)) return RUB;
    if (block(cube, RDF, RD, DF, RF)) return RDF;
    if (block(cube, LDF, LD, DF, LF)) return LDF;
    if (block(cube, LDB, LD, DB, LB)) return LDB;
    if (block(cube, RDB, RD, DB, RB)) return RDB;

    throw std::invalid_argument("No 2x2x2 block present.");
}
