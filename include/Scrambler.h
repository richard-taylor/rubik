
#ifndef SCRAMBLER_H
#define SCRAMBLER_H

class Cube;
class Sequence;

/**
Class to represent the application of a sequence of cube twists to a cube.
*/
class Scrambler
{
public:
    Scrambler();

    void scramble(Cube &cube, const Sequence &twists) const;
};

#endif
