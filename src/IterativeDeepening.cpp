
#include <iostream>
#include <set>
#include <stack>
#include "CubePattern.h"
#include "IterativeDeepening.h"

#define SAY(X) std::cout << X << std::endl;

IterativeDeepening::IterativeDeepening()
{
}

struct Position
{
    Cube cube;
    Sequence twists;
};

Sequence IterativeDeepening::try_depth(int depth,
                                       const Cube &cube,
                                       const CubePattern &pattern) const
{
    std::set<Cube> seen;
    std::stack<Position> stack;
    Position position;

    position.cube = cube;
    position.twists = Sequence();

    stack.push(position);
    long tests = 0;
    long pushed = 0;

    int test_depth = 0;

    while (!stack.empty())
    {
        position = stack.top();
        stack.pop();

        int moves = position.twists.length();
        int remaining = depth - moves;

        if (remaining <= test_depth)
        {
            ++tests;

            if (pattern.on(position.cube))
            {
                SAY(tests << " tests. " << pushed << " pushed.");
                return position.twists;
            }
        }
        else
        {
            for (int f = 0; f < 6; f++)
            {
                if (position.twists.nextFace(Face(f)))
                {
                    for (int t = 1; t <= 3; t++)
                    {
                        Twist twist = Twist(Face(f), t);
                        Position next = position;

                        next.cube.twist(twist);

                        if (seen.find(next.cube) == seen.end())
                        {
                            next.twists.add(twist);

                            stack.push(next);
                            pushed++;

                            seen.insert(next.cube);
                        }
                    }
                }
            }
        }
    }
    // didn't find a solution
    SAY(tests << " tests. " << pushed << " pushed.");
    SAY("no solution.");
    return Sequence();
}

Sequence IterativeDeepening::solve(const Cube &cube,
                                   const CubePattern &pattern) const
{
    if (pattern.on(cube))
    {
        SAY("The pattern is already solved.");
        return Sequence();
    }

    for (int depth = 1; depth <= MAX_MOVES; depth++)
    {
        SAY("Looking for a solution with " << depth << " turns.");
        Sequence solution = try_depth(depth, cube, pattern);

        if (solution.length() > 0)
            return solution;
    }
    SAY("No solution could be found.");
    throw std::runtime_error("No solution found for this cube.");
}
