
#include <iostream>
#include "Cache.h"
#include "CubeCacheLayer.h"

int main()
{
	Cache<CubeCacheLayer> cache(6);

	for (int i = 0; i <= cache.depth(); i++)
	{
	    std::cout << "got " << cache.count(i) << " positions." << std::endl;
	}
}
