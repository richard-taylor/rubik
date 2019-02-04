
#include "Cube.h"
#include "Scrambler.h"
#include "Sequence.h"

Scrambler::Scrambler()
{
}

void Scrambler::scramble(Cube &cube, const Sequence &twists) const
{
    for (auto t = twists.begin(); t != twists.end(); ++t)
    {
        cube.twist(t);
    }
}
