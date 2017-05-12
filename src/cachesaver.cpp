
#include <iostream>
#include "CacheBuilder.h"
#include "CubeCache.h"
#include "CubePacker.h"
//#include "CornersCacheLayer.h"
//#include "TetraCacheLayer.h"

int main()
{
    CubePacker packer;
    CubeCache  cubes(packer.BITS);
    
	CacheBuilder cubeCacheBuilder(cubes, packer);
	cubeCacheBuilder.verbose(true);
	cubeCacheBuilder.build(3);
	
	cubes.save("cache/tmp_cubes");
	
	//CacheBuilder<CornersCacheLayer> corners("cache/corners");
	//corners.verbose(true);
	//corners.build(11);
	//corners.free();
	
	//CacheBuilder<TetraCacheLayer> tetra("cache/tmp_tetra");
	//tetra.verbose(true);
	//tetra.build(15);
}
