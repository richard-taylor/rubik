
#include <cstdlib>
#include "RandomSequence.h"

RandomSequence::RandomSequence(int length)
{
    this->length = length;
}

Sequence RandomSequence::next()
{
    Sequence sequence;
    int previous = -1;
    int next;

    for (int i = 0; i < length; ++i)
    {
        while ((next = rand() % 6) == previous)
        {
        }
        sequence.add(Twist(Face(next), rand() % 3 + 1));
        previous = next;
    }
    return sequence;
}
