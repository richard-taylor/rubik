
#include <cassert>
#include <map>
#include <set>
#include "Cube.h"

void sexy_test(Cube::Face a, Cube::Face b)
{
    // six sexy moves in a pair of faces returns us to solved
    Cube sexy;
    
    for (int i = 0; i < 6; i++)
    {
        sexy.twist(a, 1);
        sexy.twist(b, 1);
        sexy.twist(a, 3);
        sexy.twist(b, 3);
        
        assert(i == 5 ? sexy.solved() : !sexy.solved());
    }
}

int main()
{
    // construct a Cube
    Cube cube;

    // should be less than 15 bytes
    // since we create lots, they need to be as small as practically possible.
    assert(sizeof(cube) < 15);
    
    // should be solved initially
    assert(cube.solved());
    
    // twist about each face
    cube.twist(Cube::L, 1);
    cube.twist(Cube::R, 1);
    cube.twist(Cube::U, 1);
    cube.twist(Cube::D, 1);
    cube.twist(Cube::F, 1);
    cube.twist(Cube::B, 1);
    
    // should be not solved now
    assert(!cube.solved());
    
    // two more cubes
    Cube a_cube;
    Cube b_cube;
    assert(cube != a_cube);
    assert(cube != b_cube);
    
    // should be equal at first
    assert(a_cube == b_cube);
    
    // then different if we make different moves
    a_cube.twist(Cube::L, 1);
    b_cube.twist(Cube::R, 1);
    assert(a_cube != b_cube);
    
    // if cubes are different then one is less than the other
    assert(((a_cube < b_cube) && !(b_cube < a_cube)) ||
           ((b_cube < a_cube) && !(a_cube < b_cube)));
            
    // copy constructor should be by value not reference
    Cube c_cube = b_cube;
    assert(b_cube == c_cube);
    c_cube.twist(Cube::U, 1);
    assert(b_cube != c_cube);
    
    // should be able to make a set of cubes
    std::set<Cube> cube_set;
    cube_set.insert(a_cube);
    cube_set.insert(b_cube);
    cube_set.insert(c_cube);
    assert(cube_set.size() == 3);
    assert(cube_set.find(a_cube) != cube_set.end());
    assert(cube_set.find(b_cube) != cube_set.end());
    assert(cube_set.find(c_cube) != cube_set.end());
    
    // should be able to use a cube as a key in a map
    std::map<Cube, int> count_map;
    count_map[a_cube] = 1;
    count_map[b_cube] = 2;
    count_map[c_cube] = 3;
    assert(count_map[a_cube] == 1);
    assert(count_map[b_cube] == 2);
    assert(count_map[c_cube] == 3);
    
    // check that each twist and its inverse are consistent
    Cube twisty;
        
    twisty.twist(Cube::L, 1); assert(!twisty.solved());
    twisty.twist(Cube::L, 3); assert(twisty.solved());       
    twisty.twist(Cube::L, 2); assert(!twisty.solved());
    twisty.twist(Cube::L, 2); assert(twisty.solved());

    twisty.twist(Cube::R, 1); assert(!twisty.solved());
    twisty.twist(Cube::R, 3); assert(twisty.solved());       
    twisty.twist(Cube::R, 2); assert(!twisty.solved());
    twisty.twist(Cube::R, 2); assert(twisty.solved());
    
    twisty.twist(Cube::U, 1); assert(!twisty.solved());
    twisty.twist(Cube::U, 3); assert(twisty.solved());       
    twisty.twist(Cube::U, 2); assert(!twisty.solved());
    twisty.twist(Cube::U, 2); assert(twisty.solved());
    
    twisty.twist(Cube::D, 1); assert(!twisty.solved());
    twisty.twist(Cube::D, 3); assert(twisty.solved());       
    twisty.twist(Cube::D, 2); assert(!twisty.solved());
    twisty.twist(Cube::D, 2); assert(twisty.solved());
    
    twisty.twist(Cube::F, 1); assert(!twisty.solved());
    twisty.twist(Cube::F, 3); assert(twisty.solved());       
    twisty.twist(Cube::F, 2); assert(!twisty.solved());
    twisty.twist(Cube::F, 2); assert(twisty.solved());
    
    twisty.twist(Cube::B, 1); assert(!twisty.solved());
    twisty.twist(Cube::B, 3); assert(twisty.solved());       
    twisty.twist(Cube::B, 2); assert(!twisty.solved());
    twisty.twist(Cube::B, 2); assert(twisty.solved());
    
    // check that 6 sexy moves brings us back to solved
    sexy_test(Cube::R, Cube::U);
    sexy_test(Cube::F, Cube::U);
    sexy_test(Cube::L, Cube::U);
    sexy_test(Cube::B, Cube::U);
    sexy_test(Cube::R, Cube::D);
    sexy_test(Cube::F, Cube::D);
    sexy_test(Cube::L, Cube::D);
    sexy_test(Cube::B, Cube::D);
}
