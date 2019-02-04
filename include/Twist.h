
#ifndef TWIST_H
#define TWIST_H

#include "Enums.h"
#include "Typedefs.h"

/**
Class to represent turning a face by 1, 2 or 3 lots of 90 degrees.

This is the standard outer-block metric.
*/
class Twist
{
public:
    Twist() { /* for uninitilised arrays */ }

    Twist(Face face, int turns);

    Face getFace() const;
    int getTurns() const;

    Twist inverse() const;
    bool operator==(const Twist &other) const;

private:
    byte twist;
};

const Twist L(LEFT, 1);
const Twist L2(LEFT, 2);
const Twist Li(LEFT, 3);

const Twist R(RIGHT, 1);
const Twist R2(RIGHT, 2);
const Twist Ri(RIGHT, 3);

const Twist U(UP, 1);
const Twist U2(UP, 2);
const Twist Ui(UP, 3);

const Twist D(DOWN, 1);
const Twist D2(DOWN, 2);
const Twist Di(DOWN, 3);

const Twist F(FRONT, 1);
const Twist F2(FRONT, 2);
const Twist Fi(FRONT, 3);

const Twist B(BACK, 1);
const Twist B2(BACK, 2);
const Twist Bi(BACK, 3);

#endif
