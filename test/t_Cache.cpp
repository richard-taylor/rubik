
#include <cassert>
#include "Cache.h"
#include "CubeCacheLayer.h"

int main()
{
    // construct a Cache of 3 moves
    Cache<CubeCacheLayer> cache(3);
    assert(cache.depth() == 3);
    
    // count the cubes at each depth
    assert(cache.count(0) == 1);
    assert(cache.count(1) == 18);
    assert(cache.count(2) == 243);
    assert(cache.count(3) == 3240);
    
    // should find a cube that has 3 turns
    Cube cube;
    cube.twist(Cube::Twist(Cube::R, 1));
    cube.twist(Cube::Twist(Cube::U, 1));
    cube.twist(Cube::Twist(Cube::F, 1));
    assert(cache.contains(cube));
    assert(cache.contains(cube, 3));
    
    // but not at depth 1 or 2
    assert(!cache.contains(cube, 1));
    assert(!cache.contains(cube, 2));
    
    // the solution to a cube is the inverse of the scramble
    Scramble solution = cache.get_layer(cube).solution(cube);
    assert(solution.toString() == "F' U' R'");
    
    // should not find a cube that has 4 turns
    cube.twist(Cube::Twist(Cube::D, 1));
    assert(!cache.contains(cube));
    assert(!cache.contains(cube, 1));
    assert(!cache.contains(cube, 2));
    assert(!cache.contains(cube, 3));
}
