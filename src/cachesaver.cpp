
#include <iostream>
#include "CacheBuilder.h"
#include "CubeCache.h"
#include "CubePacker.h"
//#include "CornersCacheLayer.h"
//#include "TetraCacheLayer.h"

int main()
{
    CubePacker packer;
    CubeCache  cubes(packer.state_bits(), 100000000);
    
	CacheBuilder cubeCacheBuilder(cubes, packer);
	cubeCacheBuilder.verbose(true);
	cubeCacheBuilder.build(5);
	
	cubes.save("cache/cubes");
	std::cout << "saved positions = " << cubes.count() << std::endl;
	std::cout << "table size = " << cubes.table_used() << std::endl;
	std::cout << "table over = " << cubes.table_waste() << std::endl;
	
	//CacheBuilder<CornersCacheLayer> corners("cache/corners");
	//corners.verbose(true);
	//corners.build(11);
	//corners.free();
	
	//CacheBuilder<TetraCacheLayer> tetra("cache/tmp_tetra");
	//tetra.verbose(true);
	//tetra.build(15);
}
