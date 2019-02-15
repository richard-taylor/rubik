
#include <stdexcept>
#include "Block3x2x2.h"
#include "Cube.h"

static inline void set(CornerSlot *corners,
                       CornerSlot c1,
                       CornerSlot c2,
                       EdgeSlot *edges,
                       EdgeSlot e1,
                       EdgeSlot e2,
                       EdgeSlot e3,
                       EdgeSlot e4,
                       EdgeSlot e5)
{
    corners[0] = c1;
    corners[1] = c2;

    edges[0] = e1;
    edges[1] = e2;
    edges[2] = e3;
    edges[3] = e4;
    edges[4] = e5;
}

Block3x2x2::Block3x2x2(CornerSlot fixedCorner)
{
    //static Corner solvedCorners[] = { RUF, LUF, LUB ,RUB, RDF, LDF, LDB, RDB };
    //static Edge solvedEdges[] = { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB };
    switch (fixedCorner)
    {
        case RUF:
            set(corners[0], RUF, LUF, edges[0], RU, UF, RF, LU, LF);
            set(corners[1], RUF, RDF, edges[1], RU, UF, RF, RD, DF);
            set(corners[2], RUF, RUB, edges[2], RU, UF, RF, RB, UB);
            break;
        case LUF:
            set(corners[0], LUF, RUF, edges[0], LU, UF, LF, RU, RF);
            set(corners[1], LUF, LDF, edges[1], LU, UF, LF, LD, DF);
            set(corners[2], LUF, LUB, edges[2], LU, UF, LF, LB, UB);
            break;
        case LUB:
            set(corners[0], LUB, RUB, edges[0], LU, UB, LB, RU, RB);
            set(corners[1], LUB, LDB, edges[1], LU, UB, LB, LD, DB);
            set(corners[2], LUB, LUF, edges[2], LU, UB, LB, LF, UF);
            break;
        case RUB:
            set(corners[0], RUB, LUB, edges[0], RU, UB, RB, LU, LB);
            set(corners[1], RUB, RDB, edges[1], RU, UB, RB, RD, DB);
            set(corners[2], RUB, RUF, edges[2], RU, UB, RB, RF, UF);
            break;
        case RDF:
            set(corners[0], RDF, LDF, edges[0], RD, DF, RF, LD, LF);
            set(corners[1], RDF, RUF, edges[1], RD, DF, RF, RU, UF);
            set(corners[2], RDF, RDB, edges[2], RD, DF, RF, RD, DB);
            break;
        case LDF:
            set(corners[0], LDF, RDF, edges[0], LD, DF, LF, RD, RF);
            set(corners[1], LDF, LUF, edges[1], LD, DF, LF, LU, UF);
            set(corners[2], LDF, LDB, edges[2], LD, DF, LF, LB, DB);
            break;
        case LDB:
            set(corners[0], LDB, RDB, edges[0], LD, DB, LB, RD, RB);
            set(corners[1], LDB, LUB, edges[1], LD, DB, LB, LU, UB);
            set(corners[2], LDB, LDF, edges[2], LD, DB, LB, LF, DF);
            break;
        case RDB:
            set(corners[0], RDB, LDB, edges[0], RD, DB, RB, LD, LB);
            set(corners[1], RDB, RUB, edges[1], RD, DB, RB, RU, UB);
            set(corners[2], RDB, RDF, edges[2], RD, DB, RB, RF, DF);
            break;
    }
}

static inline bool block(const Cube &cube,
                         CornerSlot c1,
                         CornerSlot c2,
                         EdgeSlot e1,
                         EdgeSlot e2,
                         EdgeSlot e3,
                         EdgeSlot e4,
                         EdgeSlot e5)
{
    return cube.cornerSolved(c1) &&
           cube.cornerSolved(c2) &&
           cube.edgeSolved(e1) &&
           cube.edgeSolved(e2) &&
           cube.edgeSolved(e3) &&
           cube.edgeSolved(e4) &&
           cube.edgeSolved(e5);
}

bool Block3x2x2::on(const Cube &cube) const
{
    for (int i = 0; i < 3; i++)
    {
        if (block(cube,
                  corners[i][0],
                  corners[i][1],
                  edges[i][0],
                  edges[i][1],
                  edges[i][2],
                  edges[i][3],
                  edges[i][4]))
        {
            return true;
        }
    }
    return false;
}
