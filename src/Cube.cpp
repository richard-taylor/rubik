
#include <cstring>
#include <random>
#include <stdexcept>
#include <vector>
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

void Cube::cornerCycle(Axis axis, CornerSlot a, CornerSlot b, CornerSlot c, CornerSlot d)
{
    // a -> b -> c -> d -> a
    //
    // Assuming all the slots are ON THE SAME FACE

    Corner A = corners[a];
    Corner B = corners[b];
    Corner C = corners[c];
    Corner D = corners[d];

    corners[b] = A.rotate90(axis);
    corners[c] = B.rotate90(axis);
    corners[d] = C.rotate90(axis);
    corners[a] = D.rotate90(axis);
}

void Cube::cornerSwap(CornerSlot a, CornerSlot b)
{
    // a -> b and b -> a
    //
    // Assuming both the slots are ON THE SAME FACE

    Corner A = corners[a];
    Corner B = corners[b];

    corners[b] = A;
    corners[a] = B;
}

// Table of rotations to exchange one corner with another. 9 = no rotation.
//
// The corner order is { RUF, LUF, LUB ,RUB, RDF, LDF, LDB, RDB }
//
static int cornerEx[8][8] = {
//   RUF LUF LUB RUB RDF LDF LDB RDB
    { 9,  Y,  9,  X,  X,  9,  Y,  9 }, // RUF
    { Y,  9,  Y,  9,  9,  Z,  9,  Y }, // LUF
    { 9,  Y,  9,  Y,  X,  9,  X,  9 }, // LUB
    { X,  9,  Y,  9,  9,  Z,  9,  X }, // RUB
    { X,  9,  X,  9,  9,  Z,  9,  X }, // RDF
    { 9,  Z,  9,  Z,  Z,  9,  X,  9 }, // LDF
    { Y,  9,  X,  9,  9,  X,  9,  Z }, // LDB
    { 9,  Y,  9,  X,  X,  9,  Z,  9 }, // RDB
};

void Cube::cornerExchange(CornerSlot a, CornerSlot b)
{
    // a -> b and b -> a
    //
    // For any pair of slots. So rotations matter.

    Corner A = corners[a];
    Corner B = corners[b];

    int rotation = cornerEx[a][b];

    if (rotation < 9)
    {
        Axis axis = Axis(rotation);
        corners[b] = A.rotate90(axis);
        corners[a] = B.rotate90(axis);
    }
    else
    {
        corners[b] = A;
        corners[a] = B;
    }
}

void Cube::cornerTwist(CornerSlot a, int times)
{
    // How to twist a corner in-place depends on where it is.
    // The even slots RUF, LUB ,RDF, LDB rotate in X then Y.
    // The odd slots LUF, RUB, LDF, RDB rotate in Y then X.

    Corner A = corners[a];
    times = times % 3;

    if (a % 2 == 0)
    {
        switch (times)
        {
        case 1:
            corners[a] = A.rotate90(X).rotate90(Y);
            break;
        case 2:
            corners[a] = A.rotate90(X).rotate90(Y).rotate90(X).rotate90(Y);
            break;
        }
    }
    else
    {
        switch (times)
        {
        case 1:
            corners[a] = A.rotate90(Y).rotate90(X);
            break;
        case 2:
            corners[a] = A.rotate90(Y).rotate90(X).rotate90(Y).rotate90(X);
            break;
        }
    }
}

void Cube::edgeCycle(Axis axis, EdgeSlot a, EdgeSlot b, EdgeSlot c, EdgeSlot d)
{
    // a -> b -> c -> d -> a
    //
    // Assuming all the slots are ON THE SAME FACE

    Edge A = edges[a];
    Edge B = edges[b];
    Edge C = edges[c];
    Edge D = edges[d];

    edges[b] = A.rotate90(axis);
    edges[c] = B.rotate90(axis);
    edges[d] = C.rotate90(axis);
    edges[a] = D.rotate90(axis);
}

void Cube::edgeSwap(EdgeSlot a, EdgeSlot b)
{
    // a -> b and b -> a
    //
    // Assuming both the slots are ON THE SAME FACE

    Edge A = edges[a];
    Edge B = edges[b];

    edges[b] = A;
    edges[a] = B;
}

// Table of rotations to exchange one edge with another. 9 = no rotation.
//
// The edge order is { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB }
//
static int edgeEx[12][12] = {
//   RU UF LU UB RF LF LB RB RD DF LD DB
    { 9, Y, 9, Y, X, X, X, X, 9, Y, 9, Y }, // RU
    { Y, 9, Y, 9, Z, Z, Z, Z, Y, 9, Y, 9 }, // UF
    { 9, Y, 9, Y, X, X, X, X, 9, Y, 9, Y }, // LU
    { Y, 9, Y, 9, Z, Z, Z, Z, Y, 9, Y, 9 }, // UB
    { X, Z, X, Z, 9, 9, 9, 9, X, Z, X, Z }, // RF
    { X, Z, X, Z, 9, 9, 9, 9, X, Z, X, Z }, // LF
    { X, Z, X, Z, 9, 9, 9, 9, X, Z, X, Z }, // LB
    { X, Z, X, Z, 9, 9, X, 9, X, Z, X, Z }, // RB
    { 9, Y, 9, Y, X, X, X, X, 9, Y, 9, Y }, // RD
    { Y, 9, Y, 9, Z, Z, Z, Z, Y, 9, Y, 9 }, // DF
    { 9, Y, 9, Y, X, X, X, X, 9, Y, 9, Y }, // LD
    { Y, 9, Y, 9, Z, Z, Z, Z, Y, 9, Y, 9 }  // DB
};

void Cube::edgeExchange(EdgeSlot a, EdgeSlot b)
{
    // a -> b and b -> a
    //
    // For any pair of slots. So rotations matter.

    Edge A = edges[a];
    Edge B = edges[b];

    int rotation = edgeEx[a][b];

    if (rotation < 9)
    {
        Axis axis = Axis(rotation);
        edges[b] = A.rotate90(axis);
        edges[a] = B.rotate90(axis);
    }
    else
    {
        edges[b] = A;
        edges[a] = B;
    }
}

void Cube::edgeFlip(EdgeSlot a)
{
    // To flip an edge in-place simply rotate in X and Y and Z.
    // The order of the rotations does not matter for an edge.

    Edge A = edges[a];
    edges[a] = A.rotate90(X).rotate90(Y).rotate90(Z);
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

bool Cube::cornerSolved(CornerSlot slot) const
{
    return corners[slot] == Corner(slot);
}

Corner Cube::cornerSlot(CornerSlot slot) const
{
    return corners[slot];
}

bool Cube::edgeSolved(EdgeSlot slot) const
{
    return edges[slot] == Edge(slot);
}

Edge Cube::edgeSlot(EdgeSlot slot) const
{
    return edges[slot];
}

Cube Cube::randomise() const
{
    return randomise({}, {});
}

static std::mt19937 RandomNumberGenerator;
static bool unseeded = true;

static void seed()
{
    RandomNumberGenerator.seed(std::random_device()());
    unseeded = false;
}

static int pick(int low, int high)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(low, high);
    return dist(RandomNumberGenerator);
}

Cube Cube::randomise(const std::set<CornerSlot> &fixedCorners,
                     const std::set<EdgeSlot> &fixedEdges) const
{
    Cube result = (*this);

    if (unseeded)
        seed();

    std::vector<CornerSlot> moveableCorner;
    for (int i = 0; i < 8; i++)
    {
        if (fixedCorners.find(CornerSlot(i)) == fixedCorners.end())
        {
            moveableCorner.push_back(CornerSlot(i));
        }
    }

    std::vector<EdgeSlot> moveableEdge;
    for (int i = 0; i < 12; i++)
    {
        if (fixedEdges.find(EdgeSlot(i)) == fixedEdges.end())
        {
            moveableEdge.push_back(EdgeSlot(i));
        }
    }

    // There are 3 constraints that must be maintained to keep the cube solvable.
    //
    // 1. The total number of piece swaps must be even.
    // 2. The number of edge flips must be even.
    // 3. The number of corner twists must be a multiple of three.

    int moveable = moveableCorner.size() + moveableEdge.size();
    int swapped = 0;

    // CORNER SWAPS

    int this_corner = 0;
    int last_corner = moveableCorner.size() - 1;

    while (this_corner < last_corner && moveable > 2)
    {
        int swap_with = pick(this_corner, last_corner);

        if (swap_with != this_corner)
        {
            result.cornerExchange(moveableCorner[this_corner], moveableCorner[swap_with]);
            swapped++;
        }
        this_corner++;
        moveable--;
    }

    if (this_corner < last_corner && moveable == 2)
    {
        // These are the last two pieces so we must use them to ensure that
        // the total number of swaps is even.

        if (swapped % 2 != 0)
        {
            result.cornerExchange(moveableCorner[this_corner], moveableCorner[last_corner]);
            swapped++;
        }
        moveable--;
    }

    // EDGE SWAPS

    int this_edge = 0;
    int last_edge = moveableEdge.size() - 1;

    while (this_edge < last_edge && moveable > 2)
    {
        int swap_with = pick(this_edge, last_edge);

        if (swap_with != this_edge)
        {
            result.edgeExchange(moveableEdge[this_edge], moveableEdge[swap_with]);
            swapped++;
        }
        this_edge++;
        moveable--;
    }

    if (this_edge < last_edge && moveable == 2)
    {
        // These are the last two pieces so we must use them to ensure that
        // the total number of swaps is even.

        if (swapped % 2 != 0)
        {
            result.edgeExchange(moveableEdge[this_edge], moveableEdge[last_edge]);
            swapped++;
        }
        moveable--;
    }

    // CORNER TWISTS

    this_corner = 0;
    last_corner = moveableCorner.size() - 1;

    int twisted = 0;

    while (this_corner < last_corner)
    {
        int twists = pick(0, 2);

        if (twists > 0)
        {
            result.cornerTwist(moveableCorner[this_corner], twists);
            twisted += twists;
        }
        this_corner++;
    }
    if (twisted % 3 != 0)
    {
        result.cornerTwist(moveableCorner[last_corner], 3 - (twisted % 3));
    }

    // EDGE FLIPS

    this_edge = 0;
    last_edge = moveableEdge.size() - 1;

    int flipped = 0;

    while (this_edge < last_edge)
    {
        int flips = pick(0, 1);

        if (flips > 0)
        {
            result.edgeFlip(moveableEdge[this_edge]);
            flipped++;
        }
        this_edge++;
    }
    if (flipped % 2 != 0)
    {
        result.edgeFlip(moveableEdge[last_edge]);
    }

    return result;
}
