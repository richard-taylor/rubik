
#include <cassert>
#include "Block2x2x2.h"
#include "Cube.h"

void trio(Twist a, Twist b, Twist c, CornerSlot d)
{
    Cube cube;
    cube.twist(a);    // skew 3 adjacent faces
    cube.twist(b);
    cube.twist(c);

    Block2x2x2 f;
    assert(f.on(cube));
    assert(d == f.fixedCorner(cube));
}

int main()
{
    Block2x2x2 block;
    Cube cube;

    // There are 8 2x2x2 blocks on a solved cube
    assert(block.on(cube));

    cube.twist(R);
    assert(block.on(cube));    // 4 remaining on the left side

    cube.twist(B);
    assert(block.on(cube));    // 2 remaining on the left front

    cube.twist(D);
    assert(block.on(cube));    // 1 remaining on the upper left front

    cube.twist(L);
    assert(!block.on(cube));    // no 2x2x2 blocks

    // check all 8 blocks
    trio(L, D, B, RUF);
    trio(R, D, B, LUF);
    trio(R, D, F, LUB);
    trio(L, D, F, RUB);
    trio(L, U, B, RDF);
    trio(R, U, B, LDF);
    trio(R, U, F, LDB);
    trio(L, U, F, RDB);
}
