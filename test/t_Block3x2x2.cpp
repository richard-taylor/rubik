
#include <cassert>
#include "Block3x2x2.h"
#include "Cube.h"

void faces(Twist a, Twist b, CornerSlot c, CornerSlot d, EdgeSlot e)
{
    Cube cube;
    cube.twist(a);    // skew two adjacent faces
    cube.twist(b);

    Block3x2x2 f(c);
    assert(f.on(cube));                 // block on one side
    assert(e == f.middleEdge(cube));

    Block3x2x2 g(d);
    assert(g.on(cube));                 // block on the other side
    assert(e == g.middleEdge(cube));
}

int main()
{
    Block3x2x2 block(RUF);
    Cube cube;

    assert(block.on(cube));

    cube.twist(B);
    assert(block.on(cube));

    cube.twist(D);
    assert(block.on(cube));

    cube.twist(L);
    assert(!block.on(cube));

    // check all 12 blocks
    faces(L, U, RDF, RDB, RD);
    faces(R, U, LDF, LDB, LD);
    faces(F, U, RDB, LDB, DB);
    faces(B, U, RDF, LDF, DF);
    faces(R, B, LUF, LDF, LF);
    faces(L, B, RUF, RDF, RF);
    faces(R, D, LUB, LUF, LU);
    faces(L, D, RUB, RUF, RU);
    faces(B, D, LUF, RUF, UF);
    faces(F, D, LUB, RUB, UB);
    faces(L, F, RDB, RUB, RB);
    faces(R, F, LDB, LUB, LB);
}
