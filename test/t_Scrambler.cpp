
#include <cassert>
#include "Cube.h"
#include "Scrambler.h"
#include "Sequence.h"

int main()
{
    // construct a Cube and a Scrambler
    Cube cube;
    Scrambler scrambler;

    // should be solved initially
    assert(cube.solved());

    // build up a scramble
    Sequence scramble;
    scramble.add(L);
    scramble.add(R2);
    scramble.add(Ui);
    scramble.add(D2);
    scramble.add(Fi);
    scramble.add(B2);

    // apply it to the cube
    scrambler.scramble(cube, scramble);

    // should be not solved now
    assert(!cube.solved());

    // now apply the inverse scramble to the cube
    scrambler.scramble(cube, scramble.inverse());

    // should be solved again
    assert(cube.solved());
}
