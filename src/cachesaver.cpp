
#include <iostream>
#include "Cache.h"
#include "CacheCube.h"

int main()
{
	Cache<CacheCube> cache(6);

	for (int i = 0; i <= cache.depth(); i++)
	{
	    std::cout << "got " << cache.count(i) << " positions." << std::endl;
	}
}
