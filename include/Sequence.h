
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include "Twist.h"

/**
Class to represent a linear sequence of cube twists.

A sequence can be extended by adding individual twists or by adding
other sequences.

The inverse of a sequence is defined as the sequence which undoes the
affect of the original sequence. In other words, if you start with a
cube in a any state, apply the sequence of twists followed by the 
inverse sequence of twists, then the cube will be back in the starting
state.
*/
class Sequence
{
public:
    /**
    Create an empty sequence.
    */
    Sequence();

    /**
    Return the number of twists are in the sequence.
    */
    int length() const;

    /**
    Add a twist to the end of this sequence.
    */
    void add(Twist twist);

    /**
    Can we add a turn of the given face next?

    To avoid equivalent sequences like "F F" and "F2" and also "L R" and "R L";
    use this method to check whether it makes sense to add a turn of the given
    face to the current sequence.
    */
    bool nextFace(Face face) const;

    /**
    Return the last twist in the sequence.
    */
    Twist last() const;

    /**
    Return the inverse sequence.
    */
    Sequence inverse() const;

    /**
    Add another sequence to the end of this one.
    */
    void append(const Sequence &other);

    // iterators
    typedef std::vector<Twist>::const_iterator const_iterator;
    //
    const_iterator begin() const;
    const_iterator end() const;

private:
    std::vector<Twist> twists;
};

#endif
