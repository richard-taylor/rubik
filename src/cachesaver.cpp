
#include <iostream>
#include "CubeCache.h"

int main()
{
	CubeCache cache(6);

	for (int i = 0; i <= cache.depth(); i++)
	{
	    std::cout << "got " << cache.count(i) << " positions." << std::endl;
	}
}
