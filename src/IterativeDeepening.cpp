
#include <stack>
#include "CubePattern.h"
#include "IterativeDeepening.h"
#include "Logging.h"

IterativeDeepening::IterativeDeepening()
{
}

struct Position
{
    Cube cube;
    Sequence twists;
};

std::vector<Sequence> IterativeDeepening::try_depth(
    int depth, bool firstOnly, const Cube &cube, const CubePattern &pattern) const
{
    std::vector<Sequence> results;
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

            if (pattern.search(position.cube, position.twists, results))
            {
                if (firstOnly)
                    return results;
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
                        next.twists.add(twist);

                        stack.push(next);
                        pushed++;
                    }
                }
            }
        }
    }
    LOG_DEBUG << tests << " tests. " << pushed << " pushed.";

    return results;
}

static std::vector<Sequence> asIs(const Cube &cube, const CubePattern &pattern)
{
    std::vector<Sequence> results;

    if (pattern.search(cube, Sequence(), results))
    {
        if (results[0].length() < 1)
        {
            LOG_INFO << "The pattern is already solved.";
        }
    }
    return results;
}

Sequence IterativeDeepening::solve(const Cube &cube,
                                   const CubePattern &pattern) const
{
    std::vector<Sequence> solutions = asIs(cube, pattern);

    if (solutions.size() > 0)
    {
        return solutions[0];
    }

    for (int depth = 1; depth <= MAX_MOVES; depth++)
    {
        LOG_INFO << "Looking for a solution with " << depth << " turns.";
        solutions = try_depth(depth, true, cube, pattern);

        if (solutions.size() > 0)
            return solutions[0];
    }
    throw std::runtime_error("No solution found for this cube.");
}

std::vector<Sequence> IterativeDeepening::allSolutions(
    const Cube &cube, const CubePattern &pattern) const
{
    std::vector<Sequence> solutions = asIs(cube, pattern);

    if (solutions.size() > 0)
    {
        return solutions;
    }

    for (int depth = 1; depth <= MAX_MOVES; depth++)
    {
        LOG_INFO << "Looking for a solution with " << depth << " turns.";
        solutions = try_depth(depth, false, cube, pattern);

        if (solutions.size() > 0)
            return solutions;
    }
    throw std::runtime_error("No solution found for this cube.");
}
