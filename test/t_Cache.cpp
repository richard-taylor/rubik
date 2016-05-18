
#include <cassert>
#include "CubeCache.h"
#include "CubeCacheLayer.h"
#include "CornersCache.h"
#include "CornersCacheLayer.h"
#include "CacheBuilder.h"

void test_cube_cache()
{
    // construct a cube position cache of 3 moves
    CacheBuilder<CubeCacheLayer> cubes("/tmp/cubes");
	cubes.verbose(true);
	cubes.build(3);
    
    // load the cache
    CubeCache cache("/tmp/cubes");
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
    Scramble solution = cache.solution(cube);
    assert(solution.toString() == "F' U' R'");
    
    // should not find a cube that has 4 turns
    cube.twist(Cube::Twist(Cube::D, 1));
    assert(!cache.contains(cube));
    assert(!cache.contains(cube, 1));
    assert(!cache.contains(cube, 2));
    assert(!cache.contains(cube, 3));
}

void test_corners_cache()
{
    // build a cache to depth 4
    CacheBuilder<CornersCacheLayer> corners("/tmp/corners");
	corners.verbose(false);
	corners.build(4);
    
    // load the cache
    CornersCache cache("/tmp/corners");
    assert(cache.depth() == 4);
    
    // count the cubes at each depth
    assert(cache.count(0) == 1);
    assert(cache.count(1) == 18);
    assert(cache.count(2) == 243);
    assert(cache.count(3) == 2874);
    assert(cache.count(4) == 28000);
    
    // should find a cube that has 4 turns
    Cube cube;
    cube.twist(Cube::Twist(Cube::R, 1));
    cube.twist(Cube::Twist(Cube::U, 1));
    cube.twist(Cube::Twist(Cube::F, 1));
    cube.twist(Cube::Twist(Cube::D, 1));
    assert(cache.contains(cube));
    assert(cache.contains(cube, 4));
    
    // but not at depth 1 or 2 or 3
    assert(!cache.contains(cube, 1));
    assert(!cache.contains(cube, 2));
    assert(!cache.contains(cube, 3));
    
    // should not find a cube that has 5 turns
    cube.twist(Cube::Twist(Cube::L, 1));
    assert(!cache.contains(cube));
    assert(!cache.contains(cube, 1));
    assert(!cache.contains(cube, 2));
    assert(!cache.contains(cube, 3));
    assert(!cache.contains(cube, 4));
}

int main()
{
    test_cube_cache();
    test_corners_cache();
}
