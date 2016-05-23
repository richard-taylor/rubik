
#include <iostream>
#include <stack>
#include "IterativeDeepening.h"

#define SAY(X) std::cout << X << std::endl;

const Cube::Twist noTwist;

extern bool cant_follow(int last, int next);

IterativeDeepening::IterativeDeepening()
{
    cubes = new CubeCache("cache/tmp_cubes");
    corners = new CornersCache("cache/tmp_corners");
}

bool IterativeDeepening::can_solve_in_less(int moves, const Cube &cube) const
{
    if (moves >= corners->depth())
        return true;
        
    while (--moves >= 0)
    {
        if (corners->contains(cube, moves))
            return true;
    }
    return false;
}

struct Position
{
    Cube cube;
    Scramble scramble;
};

Scramble IterativeDeepening::try_depth(int depth, const Cube &cube) const
{
    SAY("trying depth " << depth);
    
    std::stack<Position> stack;
    Position position;
    
    position.cube = cube;
    position.scramble = Scramble();
    
    stack.push(position);
    int tests = 0;
    
    while (!stack.empty())
    {
        position = stack.top();
        stack.pop();
        
        int moves = position.scramble.length();
        int remaining = depth - moves;
        
        if (remaining <= cubes->depth())
        {
            // test this position
            ++tests;
            
            if (cubes->contains(position.cube))
            {
                position.scramble.append(cubes->solution(position.cube));
                return position.scramble;
            }
        }
        else
        {
            // add another twist
            Cube::Twist twist = position.scramble.last();

            int lastFace = (twist == noTwist) ? -1 : twist.getFace();
            
            Position next;
            
            for (int f = 0; f < 6; f++)
            {
                if (cant_follow(lastFace, f))
                    continue;
                    
                for (int t = 1; t <= 3; t++)
                {
                    Cube::Twist next_twist((Cube::Face)f, t);
                
                    next.cube = position.cube;
                    next.cube.twist(next_twist);
                
                    next.scramble = position.scramble;
                    next.scramble.add(next_twist);
                    
                    if (can_solve_in_less(remaining, next.cube))
                        stack.push(next);
                }
            }
        }
    }
    // didn't find a solution
    SAY("no solution after " << tests << " tests.");
    return Scramble();
}

Scramble IterativeDeepening::solve(const Cube &cube) const
{
    if (cubes->contains(cube))
        return cubes->solution(cube);
 
    for (int depth = cubes->depth() + 1; depth <= MAX_MOVES; depth++)
    {
        Scramble solution = try_depth(depth, cube);
        
        if (solution.length() > 0)
            return solution;
    }       
    return Scramble();
}
