
#include <cassert>
#include "Block2x2x2.h"
#include "Cube.h"

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
}
