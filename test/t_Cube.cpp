
#include <cassert>
#include <map>
#include <set>
#include "Cube.h"

void sexy_test(Twist a, Twist b)
{
    // six sexy moves in a pair of faces returns us to solved
    Cube sexy;

    for (int i = 0; i < 6; i++)
    {
        sexy.twist(a);
        sexy.twist(b);
        sexy.twist(a.inverse());
        sexy.twist(b.inverse());

        assert(i == 5 ? sexy.solved() : !sexy.solved());
    }
}

int main()
{
    // construct a Cube
    Cube cube;

    // should be solved initially
    assert(cube.solved());

    // twist about each face
    cube.twist(L);
    cube.twist(R);
    cube.twist(U);
    cube.twist(D);
    cube.twist(F);
    cube.twist(B);

    // should be not solved now
    assert(!cube.solved());

    // two more cubes
    Cube a_cube;
    Cube b_cube;
    assert(cube != a_cube);
    assert(cube != b_cube);

    // should be equal at first
    assert(a_cube == b_cube);

    // then different if we make different moves
    a_cube.twist(L);
    b_cube.twist(R);
    assert(a_cube != b_cube);

    // if cubes are different then one is less than the other
    assert(((a_cube < b_cube) && !(b_cube < a_cube)) ||
           ((b_cube < a_cube) && !(a_cube < b_cube)));

    // copy constructor should be by value not reference
    Cube c_cube = b_cube;
    assert(b_cube == c_cube);
    c_cube.twist(U);
    assert(b_cube != c_cube);

    // should be able to make a set of cubes
    std::set<Cube> cube_set;
    cube_set.insert(a_cube);
    cube_set.insert(b_cube);
    cube_set.insert(c_cube);
    assert(cube_set.size() == 3);
    assert(cube_set.find(a_cube) != cube_set.end());
    assert(cube_set.find(b_cube) != cube_set.end());
    assert(cube_set.find(c_cube) != cube_set.end());

    // should be able to use a cube as a key in a map
    std::map<Cube, int> count_map;
    count_map[a_cube] = 1;
    count_map[b_cube] = 2;
    count_map[c_cube] = 3;
    assert(count_map[a_cube] == 1);
    assert(count_map[b_cube] == 2);
    assert(count_map[c_cube] == 3);

    // check that each twist and its inverse are consistent
    Cube twisty;

    twisty.twist(L);  assert(!twisty.solved());
    twisty.twist(Li); assert(twisty.solved());
    twisty.twist(L2); assert(!twisty.solved());
    twisty.twist(L2); assert(twisty.solved());

    twisty.twist(R);  assert(!twisty.solved());
    twisty.twist(Ri); assert(twisty.solved());
    twisty.twist(R2); assert(!twisty.solved());
    twisty.twist(R2); assert(twisty.solved());

    twisty.twist(U);  assert(!twisty.solved());
    twisty.twist(Ui); assert(twisty.solved());
    twisty.twist(U2); assert(!twisty.solved());
    twisty.twist(U2); assert(twisty.solved());

    twisty.twist(D);  assert(!twisty.solved());
    twisty.twist(Di); assert(twisty.solved());
    twisty.twist(D2); assert(!twisty.solved());
    twisty.twist(D2); assert(twisty.solved());

    twisty.twist(F);  assert(!twisty.solved());
    twisty.twist(Fi); assert(twisty.solved());
    twisty.twist(F2); assert(!twisty.solved());
    twisty.twist(F2); assert(twisty.solved());

    twisty.twist(B);  assert(!twisty.solved());
    twisty.twist(Bi); assert(twisty.solved());
    twisty.twist(B2); assert(!twisty.solved());
    twisty.twist(B2); assert(twisty.solved());

    // check that 6 sexy moves brings us back to solved
    sexy_test(R, U);
    sexy_test(F, U);
    sexy_test(L, U);
    sexy_test(B, U);
    sexy_test(R, D);
    sexy_test(F, D);
    sexy_test(L, D);
    sexy_test(B, D);

    // check individual corners and edges
    Cube c8e12;
    assert(c8e12.cornerSolved(RUF));
    assert(c8e12.edgeSolved(RU));
    assert(c8e12.cornerSolved(LUF));
    assert(c8e12.edgeSolved(LU));

    c8e12.twist(R2);
    assert(!c8e12.cornerSolved(RUF));
    assert(!c8e12.edgeSolved(RU));
    assert(c8e12.cornerSolved(LUF));
    assert(c8e12.edgeSolved(LU));

    // randomised cubes should be different
    Cube solved;
    Cube random1 = solved.randomise();
    Cube random2 = solved.randomise();

    assert(random1 != solved);
    assert(random2 != solved);
    assert(random1 != random2);

    // randomise while keeping 2 corners and 2 edges fixed
    Cube random3 = solved.randomise({ RUF, LUF }, { RU, UF });
    assert(!random3.solved());
    assert(random3.cornerSolved(RUF));
    assert(random3.cornerSolved(LUF));
    assert(random3.edgeSolved(RU));
    assert(random3.edgeSolved(UF));
}
