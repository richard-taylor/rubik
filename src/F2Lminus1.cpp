
#include <stdexcept>
#include "Block3x2x2.h"
#include "Cube.h"
#include "F2Lminus1.h"

F2Lminus1::F2Lminus1(EdgeSlot middleEdge)
{
    switch (middleEdge)
    {
        case RU:
            set(0, RUB, RUF, RDB, RU, RB, UB, RF, UF, RD, DB);
            set(1, RUB, RUF, RDF, RU, RB, UB, RF, UF, RD, DF);
            set(2, RUB, RUF, LUF, RU, RB, UB, RF, UF, LU, LF);
            set(3, RUB, RUF, LUB, RU, RB, UB, RF, UF, LU, LB);
            break;
        case UF:
            set(0, LUF, RUF, LUB, LU, LF, RU, RF, UF, UB, LB);
            set(1, LUF, RUF, RUB, LU, LF, RU, RF, UF, UB, RB);
            set(2, LUF, RUF, RDF, LU, LF, RU, RF, UF, RD, DF);
            set(3, LUF, RUF, LDF, LU, LF, RU, RF, UF, LD, DF);
            break;
        case LU:
            set(0, LUB, LUF, RUB, LU, UB, LB, UF, LF, RU, RB);
            set(1, LUB, LUF, RUF, LU, UB, LB, UF, LF, RU, RF);
            set(2, LUB, LUF, LDF, LU, UB, LB, UF, LF, LD, DF);
            set(3, LUB, LUF, LDB, LU, UB, LB, UF, LF, LD, DB);
            break;
        case UB:
            set(0, RUB, LUB, RUF, UB, RU, RB, LU, LB, UF, RF);
            set(1, RUB, LUB, LUF, UB, RU, RB, LU, LB, UF, LF);
            set(2, RUB, LUB, LDB, UB, RU, RB, LU, LB, LD, DB);
            set(3, RUB, LUB, RDB, UB, RU, RB, LU, LB, RD, DB);
            break;
        case RF:
            set(0, RDF, RUF, LUF, RF, RD, RU, DF, UF, LF, LU);
            set(1, RDF, RUF, LDF, RF, RD, RU, DF, UF, LF, LD);
            set(2, RDF, RUF, RUB, RF, RD, RU, DF, UF, UB, RB);
            set(3, RDF, RUF, RDB, RF, RD, RU, DF, UF, RB, DB);
            break;
        case LF:
            set(0, LDF, LUF, LDB, LD, LU, DF, UF, LF, LB, DB);
            set(1, LDF, LUF, LUB, LD, LU, DF, UF, LF, LB, UB);
            set(2, LDF, LUF, RUF, LD, LU, DF, UF, LF, RU, RF);
            set(3, LDF, LUF, RDF, LD, LU, DF, UF, LF, RD, RF);
            break;
        case LB:
            set(0, LUB, LDB, RDB, LB, LU, LD, UB, DB, RB, RD);
            set(1, LUB, LDB, RUB, LB, LU, LD, UB, DB, RB, RU);
            set(2, LUB, LDB, LDF, LB, LU, LD, UB, DB, DF, LF);
            set(3, LUB, LDB, LUF, LB, LU, LD, UB, DB, LF, UF);
            break;
        case RB:
            set(0, RUB, RDB, RUF, RU, RD, UB, DB, RB, RF, UF);
            set(1, RUB, RDB, RDF, RU, RD, UB, DB, RB, RF, DF);
            set(2, RUB, RDB, LDB, RU, RD, UB, DB, RB, LD, LB);
            set(3, RUB, RDB, LUB, RU, RD, UB, DB, RB, LU, LB);
            break;
        case RD:
            set(0, RDF, RDB, LDF, RD, DF, RF, DB, RB, LD, LF);
            set(1, RDF, RDB, LDB, RD, DF, RF, DB, RB, LD, LB);
            set(2, RDF, RDB, RUB, RD, DF, RF, DB, RB, RU, UB);
            set(3, RDF, RDB, RUF, RD, DF, RF, DB, RB, RU, UF);
            break;
        case DF:
            set(0, LDF, RDF, LDB, DF, LD, LF, RD, RF, DB, LB);
            set(1, LDF, RDF, RDB, DF, LD, LF, RD, RF, DB, RB);
            set(2, LDF, RDF, RUF, DF, LD, LF, RD, RF, RU, UF);
            set(3, LDF, RDF, LUF, DF, LD, LF, RD, RF, LU, UF);
            break;
        case LD:
            set(0, LDF, LDB, LUF, LD, LF, DF, LB, DB, LU, UF);
            set(1, LDF, LDB, LUB, LD, LF, DF, LB, DB, LU, UB);
            set(2, LDF, LDB, RDB, LD, LF, DF, LB, DB, RD, RB);
            set(3, LDF, LDB, RDF, LD, LF, DF, LB, DB, RD, RF);
            break;
        case DB:
            set(0, RDB, LDB, RDF, RD, RB, LD, LB, DB, DF, RF);
            set(1, RDB, LDB, LDF, RD, RB, LD, LB, DB, DF, LF);
            set(2, RDB, LDB, LUB, RD, RB, LD, LB, DB, LU, UB);
            set(3, RDB, LDB, RUB, RD, RB, LD, LB, DB, RU, UB);
            break;
    }
}

void F2Lminus1::set(int index,
                    CornerSlot a,
                    CornerSlot b,
                    CornerSlot c,
                    EdgeSlot d,
                    EdgeSlot e,
                    EdgeSlot f,
                    EdgeSlot g,
                    EdgeSlot h,
                    EdgeSlot i,
                    EdgeSlot j)
{
    corners[index][0] = a;
    corners[index][1] = b;
    corners[index][2] = c;

    edges[index][0] = d;
    edges[index][1] = e;
    edges[index][2] = f;
    edges[index][3] = g;
    edges[index][4] = h;
    edges[index][5] = i;
    edges[index][6] = j;
}

static inline bool block(const Cube &cube, const CornerSlot *c, const EdgeSlot *e)
{
    return cube.cornerSolved(c[0]) &&
           cube.cornerSolved(c[1]) &&
           cube.cornerSolved(c[2]) &&
           cube.edgeSolved(e[0]) &&
           cube.edgeSolved(e[1]) &&
           cube.edgeSolved(e[2]) &&
           cube.edgeSolved(e[3]) &&
           cube.edgeSolved(e[4]) &&
           cube.edgeSolved(e[5]) &&
           cube.edgeSolved(e[6]);
}

bool F2Lminus1::on(const Cube &cube) const
{
    for (int i = 0; i < 4; i++)
    {
        if (block(cube, corners[i], edges[i]))
        {
            return true;
        }
    }
    return false;
}
