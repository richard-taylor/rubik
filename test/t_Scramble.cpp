
#include <cassert>
#include "Scramble.h"

const Cube::Twist R(Cube::R, 1);
const Cube::Twist U(Cube::U, 1);
const Cube::Twist D(Cube::D, 1);
const Cube::Twist F(Cube::F, 1);

const Cube::Twist R2(Cube::R, 2);
const Cube::Twist D2(Cube::D, 2);

const Cube::Twist Fi(Cube::F, 3);

int main()
{
    // construct a Scramble
    Scramble scramble;

    // should be empty
    assert(scramble.length() == 0);

    // adding twists
    scramble.add(R2);
    assert(scramble.length() == 1);
    scramble.add(D);
    assert(scramble.length() == 2);
    
    // apply to a cube, changing it
    Cube cube;
    assert(cube.solved());
    scramble.apply(cube);
    assert(!cube.solved());
    
    // apply the inverse, undoing the scramble
    scramble.inverse().apply(cube);
    assert(cube.solved());
    
    // return a new scrambled cube, leaving the original unchanged
    Cube unsolved = scramble.of(cube);
    assert(cube.solved());
    assert(!unsolved.solved());
    
    // string version (with 1, 2, 3 turns)
    scramble.add(Fi);
    assert(scramble.toString() == "R2 D F'");
    
    // check the last twist
    Cube::Twist last = scramble.last();
    assert(last.getFace() == Cube::F);
    assert(last.getTurns() == 3);
    
    // construct a random scramble
    Scramble random(20);
    assert(random.length() == 20);
    
    // construct another random scramble
    Scramble random2(20);
    assert(random2.length() == 20);
    
    // two random scrambles are unlikely to be equivalent
    assert(!random.equivalent(random2));
    
    // make two equivalent scrambles
    Scramble s1;
    s1.add(R);
    s1.add(U);
    s1.add(F);
    
    Scramble s2;
    s2.add(R);
    s2.add(U);
    s2.add(D2);
    s2.add(D2);
    s2.add(F);
    
    assert(s1.equivalent(s2));
}
