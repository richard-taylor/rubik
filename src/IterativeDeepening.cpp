
#include <iostream>
#include <stack>
#include "CubePacker.h"
#include "IterativeDeepening.h"
#include "OrientPacker.h"
#include "State.h"

#define SAY(X) std::cout << X << std::endl;

IterativeDeepening::IterativeDeepening()
{
    m_cubes = NULL;
    m_orients = NULL;
}

void IterativeDeepening::set_position_cache(const CubeCache &positions)
{
    m_cubes = &positions;
}

void IterativeDeepening::set_orientation_cache(const CubeCache &orientations)
{
    m_orients = &orientations;
}

bool IterativeDeepening::can_solve_in_less(int moves, const Cube &cube) const
{
    int deepest = m_orients->depth() + 1;
    SAY("can_solve_in_less : deepest " << deepest << " moves " << moves);
    
    if (moves > deepest)
        return true;
        
    OrientPacker packer;
    State state(packer.state_bits());
    
    packer.pack(cube, state);
        
    int turns = m_orients->solution(state);
                
    if (turns < 0)
        turns = deepest;
    
    SAY("can_solve_in_less : is " << turns << " less than " << moves);
    return turns < moves;
}

struct Position
{
    Cube cube;
    Scramble scramble;
};

Scramble IterativeDeepening::try_depth(int depth, const Cube &cube) const
{
    CubePacker packer;
    State state(packer.state_bits());
        
    std::stack<Position> stack;
    Position position;
    
    position.cube = cube;
    position.scramble = Scramble();
    
    stack.push(position);
    long tests = 0;
    long pruned = 0;
    
    int test_depth = (m_cubes == NULL) ? 0 : m_cubes->depth();
    
    while (!stack.empty())
    {
        position = stack.top();
        stack.pop();
        
        int moves = position.scramble.length();
        int remaining = depth - moves;
        
        if (remaining <= test_depth)
        {
            // test this position
            ++tests;
            
            if (m_cubes == NULL)
            {
                if (position.cube.solved())
                {
                    SAY(tests << " tests. " << pruned << " pruned.");
                    return position.scramble;
                }
            }
            else
            {
                packer.pack(position.cube, state);
        
                int turns = m_cubes->solution(state);
        
                if (turns > 0)
                {
                    //position.scramble.append(cubes->solution(position.cube));
                    SAY(tests << " tests. " << pruned << " pruned.");
                    return position.scramble;
                }
            }
        }
        else
        {
            if (m_orients == NULL || can_solve_in_less(remaining + 1, position.cube))
            {
                // add another twist

                for (Cube::Face f = Cube::L; f <= Cube::B; f = Cube::Face(f + 1))
                {
                    if (position.scramble.can_add(f))
                    {
                        for (int t = 1; t <= 3; t++)
                        {
                            Cube::Twist twist = Cube::Twist(f, t);
                        
                            Position next = position;
                        
                            next.cube.twist(twist);
                            next.scramble.add(twist);
                        
                            stack.push(next);
                        }
                    }
                }
            }
            else
            {
                pruned++;
            }
        }
    }
    // didn't find a solution
    SAY(tests << " tests. " << pruned << " pruned.");
    SAY("no solution.");
    return Scramble();
}

Scramble IterativeDeepening::solve(const Cube &cube) const
{
    if (cube.solved())
    {
        SAY("The cube is already solved.");
        return Scramble();
    }
    
    int start_depth = 1;
     
    if (m_cubes != NULL)
    {
        CubePacker packer;
        State state(packer.state_bits());
        
        packer.pack(cube, state);
        
        int turns = m_cubes->solution(state);
        
        if (turns > 0)
        {
            SAY("The solution is a cached position with " << turns << " turns.");
            return Scramble();
        }
        start_depth = m_cubes->depth() + 1;
    }
 
    for (int depth = start_depth; depth <= MAX_MOVES; depth++)
    {
        SAY("Looking for a solution with " << depth << " turns.");
        Scramble solution = try_depth(depth, cube);
        
        if (solution.length() > 0)
            return solution;
    }
    SAY("No solution could be found.");       
    throw std::runtime_error("no solution found for this cube");
}
