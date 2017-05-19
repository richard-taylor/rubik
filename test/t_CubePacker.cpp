
#include <cassert>
#include "Cube.h"
#include "CubeConstants.h"
#include "CubePacker.h"
#include "State.h"

int main()
{
    Cube cube;
    CubePacker packer;

    State solved_state(packer);
    packer.pack(cube, solved_state);
    
    // one twist about each face
    cube.twist(L);
    cube.twist(R);
    cube.twist(U);
    cube.twist(D);
    cube.twist(F);
    cube.twist(B);
    
    State unsolved_state(packer);
    packer.pack(cube, unsolved_state);
    
    bool different = false;
    for (int i = 0; i < packer.state_bits(); i++)
    {
        if (solved_state.get_bit(i) != unsolved_state.get_bit(i))
            different = true;
    }
    assert(different);
    
    Cube equiv;
    // different twist order, but the same end state
    equiv.twist(R);
    equiv.twist(L);
    equiv.twist(D);
    equiv.twist(U);
    equiv.twist(B);
    equiv.twist(F);
    
    State equiv_state(packer);
    packer.pack(equiv, equiv_state);
    
    bool same = true;
    for (int i = 0; i < packer.state_bits(); i++)
    {
        if (equiv_state.get_bit(i) != unsolved_state.get_bit(i))
            same = false;
    }
    assert(same);
}
