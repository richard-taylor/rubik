
#include <cassert>
#include "Edge.h"

int main() {

    // Default orientation is OOO
    Edge edge(0);
    assert(edge.getOrientation() == Edge::OOO);

    // Getters
    Edge edge11(11, Edge::UUU);
    assert(edge11.getIndex() == 11);
    assert(edge11.getOrientation() == Edge::UUU);

    // Rotation by 90 degrees changes the orientation
    Edge edge90 = edge.rotate90(X);
    assert(edge90.getIndex() == 0);
    assert(edge90.getOrientation() == Edge::UOO);

    // Rotation by another 90 degrees restores the orientation
    Edge edge180 = edge90.rotate90(X);
    assert(edge180.getIndex() == 0);
    assert(edge180.getOrientation() == Edge::OOO);

    assert(edge180 == edge);

    // An array of solved edges
    Edge solved[] = { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB };
    for (int i = 0; i < 12; i++)
    {
        assert(solved[i].getIndex() == i);
        assert(solved[i].getOrientation() == Edge::OOO);
    }
}
