
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
