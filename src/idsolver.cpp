
#include <ctime>
#include <iostream>
#include "CubeConstants.h"
#include "IterativeDeepening.h"
#include "TrieCache.h"

void report(const Scramble &scramble, clock_t initialisation, clock_t solving)
{
    std::cout << "initialisation time: " << (((float)initialisation)/CLOCKS_PER_SEC) << std::endl;
    std::cout << "solving time: " << (((float)solving)/CLOCKS_PER_SEC) << std::endl;
    std::cout << "solution: " << scramble.toString() << std::endl;
}

int main()
{
    Cube cube;
    cube.twist(D2); cube.twist(R); cube.twist(L); cube.twist(B); cube.twist(F);
    cube.twist(Ri); cube.twist(F);  cube.twist(U2); cube.twist(Li); cube.twist(Bi);
    //cube.twist(U2); cube.twist(Li); cube.twist(R2); cube.twist(Bi); cube.twist(R);
    //cube.twist(U2); cube.twist(L);  cube.twist(B);  cube.twist(Ui); cube.twist(Di);
    //cube.twist(Bi); cube.twist(Ui); cube.twist(F2); cube.twist(D);  cube.twist(Ri);
    
    clock_t start = clock();
    
    // load the caches
    TrieCache positions("cubes-cache.binary");
    
    // set up the solver
    IterativeDeepening solver;
    solver.set_position_cache(positions);
    //
    clock_t initialised = clock();
 
    // run the solver   
    Scramble solution = solver.solve(cube);
    //
    clock_t solved = clock();
    
    report(solution, initialised - start, solved - initialised);
}
