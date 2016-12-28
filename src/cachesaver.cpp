
#include <iostream>
#include "CacheBuilder.h"
#include "CubeCacheLayer.h"
#include "CornersCacheLayer.h"
#include "TetraCacheLayer.h"

int main()
{
	//CacheBuilder<CubeCacheLayer> cubes("cache/tmp_cubes");
	//cubes.verbose(true);
	//cubes.build(6);
	
	CacheBuilder<CornersCacheLayer> corners("cache/corners");
	corners.verbose(true);
	corners.build(11);
	corners.free();
	
	//CacheBuilder<TetraCacheLayer> tetra("cache/tmp_tetra");
	//tetra.verbose(true);
	//tetra.build(15);
}
