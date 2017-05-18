
#include <cassert>
#include "Cube.h"
#include "CubeConstants.h"
#include "CubePacker.h"
#include "State.h"

int main()
{
    Cube cube;
    CubePacker packer;

    State state(packer);
    
    //assert(state.size_bits() == 80);
    
    // twist about each face
    cube.twist(L);
    cube.twist(R);
    cube.twist(U);
    cube.twist(D);
    cube.twist(F);
    cube.twist(B);
}
