
#ifndef SEQUENCESTRING_H
#define SEQUENCESTRING_H

#include <string>
#include "Sequence.h"

/**
Class that can convert between character strings and twist sequences.
*/
class SequenceString
{
public:
    SequenceString(const Sequence &sequence);
    SequenceString(const std::string &string);

    operator Sequence() const;
    operator const char*() const;

private:
    Sequence sequence;
    std::string string;
};

#endif
