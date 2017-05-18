
#include "CubePacker.h"
#include "Cube.h"
#include "State.h"

int CubePacker::state_bits()
{
    return 97; // 7 corners * 6 bits + 11 edges * 5 bits 
}

void CubePacker::pack(const Cube &cube, State &state)
{
    byte corners[8];
    byte edges[12];
    
    cube.get_pieces(corners, edges);
    
    state.set_byte(0, 0);
    
    return;
}
