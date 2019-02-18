
#include <cassert>
#include "F2Lminus1.h"
#include "Cube.h"

void pair(Twist a, Twist b, Twist c, EdgeSlot d, EdgeSlot e)
{
    Cube cube;
    cube.twist(a);         // remove a pair
    cube.twist(b);
    cube.twist(c);

    F2Lminus1 f(d);
    assert(f.on(cube));    // block on one side

    F2Lminus1 g(e);
    assert(g.on(cube));    // block on the other side
}

int main()
{
    // check all 24 pair-slots

    pair(L, U, Li, RD, DF);
    pair(R, U, Ri, LD, DB);
    pair(F, U, Fi, RD, DB);
    pair(B, U, Bi, LD, DF);

    pair(L, D, Li, RU, UB);
    pair(R, D, Ri, LU, UF);
    pair(F, D, Fi, LU, UB);
    pair(B, D, Bi, RU, UF);

    pair(U, R, Ui, LD, LF);
    pair(D, R, Di, LU, LB);
    pair(F, R, Fi, LD, LB);
    pair(B, R, Bi, LU, LF);

    pair(U, L, Ui, RD, RB);
    pair(D, L, Di, RU, RF);
    pair(F, L, Fi, RU, RB);
    pair(B, L, Bi, RD, RF);

    pair(L, F, Li, DB, RB);
    pair(R, F, Ri, UB, LB);
    pair(U, F, Ui, DB, LB);
    pair(D, F, Di, UB, RB);

    pair(L, B, Li, UF, RF);
    pair(R, B, Ri, DF, LF);
    pair(U, B, Ui, DF, RF);
    pair(D, B, Di, UF, LF);
}
