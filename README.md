# Rubik's Cube tools and solvers

This is some code I have had kicking around for a while. The 2x2x2 solver is in Python because I wanted to see if I could write an algorithm that could solve it in under a second without any fancy code optimisations.

There are some ideas from there that I want to work on for 3x3x3 cubes that I know will need to be in C++ because the scale of the problem is so much bigger.

The key idea is to generate a cache of all the positions that are 5 moves from solved. That is about half of the maximum search depth of 11. Then the search looks for one of those positions, rather than searching all the way down to the solved position. This drastically reduces the number of search steps.

On my old laptop this takes about 0.5 seconds to find all the optimal solutions to a random scramble.

(the timing in the script includes the time to generate the cache)

RT

This branch is going to use tries to store states with the leaf nodes having a count of the minimum number of turns to solve.

That should be very space efficient and fairly fast to look-up. It also avoids a lot of the faffing about with layers that have stalled the work.
