
#include <stdexcept>
#include <sstream>
#include "SequenceString.h"

static const char* name[3][6] = {
    { "L", "R", "U", "D", "F", "B" },
    { "L2", "R2", "U2", "D2", "F2", "B2" },
    { "L'", "R'", "U'", "D'", "F'", "B'" },
};

SequenceString::SequenceString(const Sequence &twists)
{
    sequence = twists;
    std::stringstream stream;
    int printed = 0;

    for (auto t = sequence.begin(); t != sequence.end(); ++t)
    {
        if (printed++ > 0)
            stream << " ";

        stream << name[ t->getTurns() - 1 ][ t->getFace() ];
    }
    string = stream.str();
}

SequenceString::operator const char*() const
{
    return string.c_str();
}
