
#include <cstring>
#include "Cube.h"

static Corner solvedCorners[] = { RUF, LUF, LUB ,RUB, RDF, LDF, LDB, RDB };
static Edge solvedEdges[] = { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB };

const int cornerBytes = sizeof(solvedCorners);
const int edgeBytes = sizeof(solvedEdges);

Cube::Cube()
{
    memcpy(corners, solvedCorners, cornerBytes);
    memcpy(edges, solvedEdges, edgeBytes);
}

bool Cube::solved() const
{
    return (memcmp(corners, solvedCorners, cornerBytes) == 0 &&
            memcmp(edges, solvedEdges, edgeBytes) == 0);
}

void Cube::cornerCycle(Axis axis, Corner a, Corner b, Corner c, Corner d)
{
    // a -> b -> c -> d -> a

    Corner A = corners[a.getIndex()];
    Corner B = corners[b.getIndex()];
    Corner C = corners[c.getIndex()];
    Corner D = corners[d.getIndex()];

    corners[b.getIndex()] = A.rotate90(axis);
    corners[c.getIndex()] = B.rotate90(axis);
    corners[d.getIndex()] = C.rotate90(axis);
    corners[a.getIndex()] = D.rotate90(axis);
}

void Cube::cornerSwap(Corner a, Corner b)
{
    Corner A = corners[a.getIndex()];
    Corner B = corners[b.getIndex()];

    corners[b.getIndex()] = A;
    corners[a.getIndex()] = B;
}

void Cube::edgeCycle(Axis axis, Edge a, Edge b, Edge c, Edge d)
{
    // a -> b -> c -> d -> a

    Edge A = edges[a.getIndex()];
    Edge B = edges[b.getIndex()];
    Edge C = edges[c.getIndex()];
    Edge D = edges[d.getIndex()];

    edges[b.getIndex()] = A.rotate90(axis);
    edges[c.getIndex()] = B.rotate90(axis);
    edges[d.getIndex()] = C.rotate90(axis);
    edges[a.getIndex()] = D.rotate90(axis);
}

void Cube::edgeSwap(Edge a, Edge b)
{
    Edge A = edges[a.getIndex()];
    Edge B = edges[b.getIndex()];

    edges[b.getIndex()] = A;
    edges[a.getIndex()] = B;
}

void Cube::twist(Twist turn)
{
    Face face = turn.getFace();
    int turns = turn.getTurns();

    switch (face)
    {
        case LEFT:
            switch (turns) {
                case 1:
                    cornerCycle(X, LUB, LUF, LDF, LDB);
                    edgeCycle(X, LU, LF, LD, LB);
                    break;
                case 2:
                    cornerSwap(LUB, LDF);
                    cornerSwap(LUF, LDB);
                    edgeSwap(LU, LD);
                    edgeSwap(LF, LB);
                    break;
                case 3:
                    cornerCycle(X, LDB, LDF, LUF, LUB);
                    edgeCycle(X, LB, LD, LF, LU);
                    break;
            }
            break;

        case RIGHT:
            switch (turns) {
                case 1:
                    cornerCycle(X, RUF, RUB, RDB, RDF);
                    edgeCycle(X, RU, RB, RD, RF);
                    break;
                case 2:
                    cornerSwap(RUF, RDB);
                    cornerSwap(RUB, RDF);
                    edgeSwap(RU, RD);
                    edgeSwap(RF, RB);
                    break;
                case 3:
                    cornerCycle(X, RDF, RDB, RUB, RUF);
                    edgeCycle(X, RF, RD, RB, RU);
                    break;
            }
            break;

        case UP:
            switch (turns) {
                case 1:
                    cornerCycle(Y, LUF, LUB, RUB, RUF);
                    edgeCycle(Y, LU, UB, RU, UF);
                    break;
                case 2:
                    cornerSwap(LUF, RUB);
                    cornerSwap(LUB, RUF);
                    edgeSwap(LU, RU);
                    edgeSwap(UF, UB);
                    break;
                case 3:
                    cornerCycle(Y, RUF, RUB, LUB, LUF);
                    edgeCycle(Y, UF, RU, UB, LU);
                    break;
            }
            break;

        case DOWN:
            switch (turns) {
                case 1:
                    cornerCycle(Y, LDF, RDF, RDB, LDB);
                    edgeCycle(Y, DF, RD, DB, LD);
                    break;
                case 2:
                    cornerSwap(LDF, RDB);
                    cornerSwap(LDB, RDF);
                    edgeSwap(DF, DB);
                    edgeSwap(LD, RD);
                    break;
                case 3:
                    cornerCycle(Y, LDB, RDB, RDF, LDF);
                    edgeCycle(Y, LD, DB, RD, DF);
                    break;
            }
            break;

        case FRONT:
            switch (turns) {
                case 1:
                    cornerCycle(Z, LUF, RUF, RDF, LDF);
                    edgeCycle(Z, LF, UF, RF, DF);
                    break;
                case 2:
                    cornerSwap(LUF, RDF);
                    cornerSwap(LDF, RUF);
                    edgeSwap(LF, RF);
                    edgeSwap(UF, DF);
                    break;
                case 3:
                    cornerCycle(Z, LDF, RDF, RUF, LUF);
                    edgeCycle(Z, DF, RF, UF, LF);
                    break;
            }
            break;

        case BACK:
            switch (turns) {
                case 1:
                    cornerCycle(Z, RUB, LUB, LDB, RDB);
                    edgeCycle(Z, RB, UB, LB, DB);
                    break;
                case 2:
                    cornerSwap(LDB, RUB);
                    cornerSwap(LUB, RDB);
                    edgeSwap(LB, RB);
                    edgeSwap(UB, DB);
                    break;
                case 3:
                    cornerCycle(Z, RDB, LDB, LUB, RUB);
                    edgeCycle(Z, DB, LB, UB, RB);
                    break;
            }
            break;
    }
}

bool Cube::operator==(const Cube &other) const
{
    return (memcmp(corners, other.corners, cornerBytes) == 0 &&
            memcmp(edges, other.edges, edgeBytes) == 0);
}

bool Cube::operator!=(const Cube &other) const
{
    return (memcmp(corners, other.corners, cornerBytes) != 0 ||
            memcmp(edges, other.edges, edgeBytes) != 0);
}

bool Cube::operator<(const Cube &other) const
{
    int cornerCmp = memcmp(corners, other.corners, cornerBytes);

    if (cornerCmp == 0)
        return (memcmp(edges, other.edges, edgeBytes) < 0);
    else
        return (cornerCmp < 0);
}

bool Cube::cornerSolved(Corner slot) const
{
    return corners[slot.getIndex()] == slot;
}

bool Cube::edgeSolved(Edge slot) const
{
    return edges[slot.getIndex()] == slot;
}
