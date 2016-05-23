
#include <iostream>
#include "CacheBuilder.h"
#include "CubeCacheLayer.h"
#include "CornersCacheLayer.h"

int main()
{
	CacheBuilder<CubeCacheLayer> cubes("cache/tmp_cubes");
	cubes.verbose(true);
	cubes.build(6);
	
	CacheBuilder<CornersCacheLayer> corners("cache/tmp_corners");
	corners.verbose(true);
	corners.build(11);
}
