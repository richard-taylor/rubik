
#include <cassert>
#include <map>
#include <set>
#include "Cube.h"

int main()
{
    // construct a Cube
    Cube cube;

    // should be less than 14 bytes
    // since we create lots, they need to be as small as practically possible.
    assert(sizeof(cube) < 14);
    
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
}
