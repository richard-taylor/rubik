
#include <map>
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
    std::ostringstream stream;
    int printed = 0;

    for (auto t = sequence.begin(); t != sequence.end(); ++t)
    {
        if (printed++ > 0)
            stream << " ";

        stream << name[ t->getTurns() - 1 ][ t->getFace() ];
    }
    string = stream.str();
}

static const std::map<std::string, Twist> twist = {
    {"L", L}, {"R", R}, {"U", U}, {"D", D}, {"F", F}, {"B", B},
    {"L2", L2}, {"R2", R2}, {"U2", U2}, {"D2", D2}, {"F2", F2}, {"B2", B2},
    {"L'", Li}, {"R'", Ri}, {"U'", Ui}, {"D'", Di}, {"F'", Fi}, {"B'", Bi}
};

SequenceString::SequenceString(const char *characters)
{
    std::istringstream stream(characters);
    std::string word;

    while (stream >> word)
    {
        try
        {
            sequence.add(twist.at(word));
        }
        catch (const std::out_of_range &e)
        {
            throw std::invalid_argument("Not a twist \"" + word + "\".");
        }
    }
}

SequenceString::operator Sequence() const
{
    return sequence;
}

SequenceString::operator const char*() const
{
    return string.c_str();
}
