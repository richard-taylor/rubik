
#include <cstring>
#include <iostream>
#include "Cube.h"

const unsigned char Cube::SOLVED_STATE[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 }; // placeholder values

Cube::Cube()
{
    memcpy(state, SOLVED_STATE, STATE_SIZE);
}

bool Cube::solved() const
{
    return (memcmp(state, SOLVED_STATE, STATE_SIZE) == 0);
}

void Cube::twist(Face face, int turns)
{
    state[face]++; // just any old change for now
}

bool Cube::operator==(const Cube &other) const
{
    return (memcmp(state, other.state, STATE_SIZE) == 0);
}

bool Cube::operator!=(const Cube &other) const
{
    return (memcmp(state, other.state, STATE_SIZE) != 0);
}
