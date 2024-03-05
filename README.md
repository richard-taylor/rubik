# Rubik's Cube tools and solvers

## 2x2x2

This is some code I have had kicking around for a long time. The 2x2x2 solver
is in Python because I wanted to see if I could write an algorithm that could
solve it in under a second without any fancy code optimisations.

The key idea is to generate a cache of all the positions that are 5 moves
from solved. That is about half of the maximum search depth of 11. Then the
search looks for one of those positions, rather than searching all the way
down to the solved position. This drastically reduces the number of search
steps.

On my old laptop this takes about 0.5 seconds to find all the optimal
solutions to a random scramble.

The timing in the script includes the time to generate the cache. If it
didn't then you might as well cache all 4 million positions and not bother
solving anything...

## 3x3x3 (version 2)

I am currently learning Rust and decided to rework some of my FMC tools in
that language. Both as a learning exercise and to apply what I learned
along the way last time - in particular I want to make them multi-threaded
to speed up the searching.

## 3x3x3 (version 1)

On the 3x3x3 cube I am interested in tools to help me practise the
Fewest Moves Challenge (FMC). These are in C++ because the scale of
the problem is so much bigger.

For example, the tool block222 will find all the shortest ways to make
a 2x2x2 block somewhere on the cube with a given scramble:

    bin/block222 "F R2 B2 D2 B2 U' R2 U L2 U B2 U' L B' F2"
    INFO: Looking for a solution with 1 turns.
    INFO: Looking for a solution with 2 turns.
    INFO: Looking for a solution with 3 turns.
    INFO: Looking for a solution with 4 turns.
    INFO: Looking for a solution with 5 turns.
    INFO: solving time: 0.963218
    solutions:
        B2 D B2 D2 R2
        B L B' D2 R2
        B L R2 U2 F
        F2 L D' F2 R2
        D2 B L B' R2
        D B2 D B2 R2
        U D2 F' D F

Here it finds 7 different ways to get a 2x2x2 block in 5 twists.
