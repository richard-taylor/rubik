
#include <cassert>
#include "Twist.h"

int main() {

    // There are 18 valid twists
    Twist L1(LEFT, 1);
    Twist L2(LEFT, 2);
    Twist L3(LEFT, 3);

    Twist R1(RIGHT, 1);
    Twist R2(RIGHT, 2);
    Twist R3(RIGHT, 3);

    Twist U1(UP, 1);
    Twist U2(UP, 2);
    Twist U3(UP, 3);

    Twist D1(DOWN, 1);
    Twist D2(DOWN, 2);
    Twist D3(DOWN, 3);

    Twist F1(FRONT, 1);
    Twist F2(FRONT, 2);
    Twist F3(FRONT, 3);

    Twist B1(BACK, 1);
    Twist B2(BACK, 2);
    Twist B3(BACK, 3);

    // Constants are defined for convenience (test equality)
    assert(L1 == L);
    assert(L2 == L2);
    assert(L3 == Li);

    assert(R1 == R);
    assert(R2 == R2);
    assert(R3 == Ri);

    assert(U1 == U);
    assert(U2 == U2);
    assert(U3 == Ui);

    assert(D1 == D);
    assert(D2 == D2);
    assert(D3 == Di);

    assert(F1 == F);
    assert(F2 == F2);
    assert(F3 == Fi);

    assert(B1 == B);
    assert(B2 == B2);
    assert(B3 == Bi);

    // Everything has an inverse
    assert(L3 == L.inverse());
    assert(L2 == L2.inverse());
    assert(L1 == Li.inverse());

    assert(R3 == R.inverse());
    assert(R2 == R2.inverse());
    assert(R1 == Ri.inverse());

    assert(U3 == U.inverse());
    assert(U2 == U2.inverse());
    assert(U1 == Ui.inverse());

    assert(D3 == D.inverse());
    assert(D2 == D2.inverse());
    assert(D1 == Di.inverse());

    assert(F3 == F.inverse());
    assert(F2 == F2.inverse());
    assert(F1 == Fi.inverse());

    assert(B3 == B.inverse());
    assert(B2 == B2.inverse());
    assert(B1 == Bi.inverse());

    // Getters (not exhaustive)
    assert(L1.getFace() == LEFT && L1.getTurns() == 1);
    assert(R2.getFace() == RIGHT && R2.getTurns() == 2);
    assert(U3.getFace() == UP && U3.getTurns() == 3);
    assert(D1.getFace() == DOWN && D1.getTurns() == 1);
    assert(F2.getFace() == FRONT && F2.getTurns() == 2);
    assert(B3.getFace() == BACK && B3.getTurns() == 3);
}
