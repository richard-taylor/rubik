
#ifndef RANDOMSEQUENCE_H
#define RANDOMSEQUENCE_H

#include "Sequence.h"

/**
Class to represent the generation of random sequences of cube twists.

This can be used to put a cube into a "random" state. Which is useful when
you want to estimate the distribution of some property across all cube states,
since the total number of states is too large to test every one.

Note that scrambling a cube with a random sequence does not produce an even
distribution of cube states. To do that you would need to pick an actual state
at random. But a random sequence of more than 40 moves is often good enough
for testing.
}
*/
class RandomSequence
{
public:
    RandomSequence(int length);
    Sequence next();

private:
    int length;
};

#endif
