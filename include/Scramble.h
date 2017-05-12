
#ifndef SCRAMBLE_H
#define SCRAMBLE_H

#include <fstream>
#include <string>
#include <vector>
#include "Cube.h"

class Scramble
{
public:
    /**
    Create an empty scramble.
    */
    Scramble();
    
    /**
    Create a random scramble of a given length.
    */
    Scramble(int length);
    
    /**
    Get the length of the scramble.
    */
    int length() const;
    
    /**
    Add a twist to the scramble.
    */
    void add(Cube::Twist twist);
    
    /**
    Can we add a turn of the given face next?
    
    To avoid equivalent sequences like "F F" and "F2" and also "L R" and "R L";
    use this method to check whether it makes sense to add a turn of the given
    face to the current scramble.
    */
    bool can_add(Cube::Face face) const;
    
    /**
    Apply the scramble to a cube.
    */
    void apply(Cube &cube) const;
    
    /**
    Return a new scrambled cube, leaving the original unchanged.
    */
    Cube of(const Cube &cube) const;

    /**
    Return the last twist in the scramble.
    */
    Cube::Twist last() const;

    /**
    Return the inverse scramble.
    */
    Scramble inverse() const;
    
    /**
    Test for equivalence (do they produce the same cube).
    */
    bool equivalent(const Scramble &other) const;
    
    /**
    Add another scramble to the end of this one.
    */
    void append(const Scramble &other);
    
    /**
    Return a string representation of the scramble.
    */
    std::string toString() const;
    
    bool read(std::istream &in, int length);
    bool write(std::ostream &out) const;
    
private:
    std::vector<Cube::Twist> twists;
};

#endif
