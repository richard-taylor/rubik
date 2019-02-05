
#include <ctime>
#include <iostream>
#include <stdexcept>
#include "Block2x2x2.h"
#include "IterativeDeepening.h"
#include "Sequence.h"
#include "SequenceString.h"

void report(const Sequence &solution, clock_t solving)
{
    std::cout << "solving time: " << (((float)solving)/CLOCKS_PER_SEC) << std::endl;
    std::cout << "solution: " << SequenceString(solution) << std::endl;
}

int main()
{
    Cube cube;
    cube.twist(D2);
    cube.twist(F);
    cube.twist(Ri);
    cube.twist(F2);
    cube.twist(Ri);
    cube.twist(Fi);
    cube.twist(U2);
    cube.twist(B);
    cube.twist(R);
    cube.twist(U2);
    cube.twist(R2);
    cube.twist(Ui);
    cube.twist(L2);
    cube.twist(Di);
    cube.twist(L2);
    cube.twist(B2);
    cube.twist(D);
    cube.twist(L2);
    cube.twist(U2);

    clock_t start = clock();

    IterativeDeepening solver;
    Block2x2x2 pattern;

    try
    {
        Sequence solution = solver.solve(cube, pattern);

        clock_t solved = clock();
        report(solution, solved - start);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "No solution found." << std::endl;
    }
}
