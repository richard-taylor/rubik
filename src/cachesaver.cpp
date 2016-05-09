
#include <iostream>
#include "Cache.h"
#include "CacheCube.h"

int main()
{
    int N = 4;
    
	Cache<CacheCube> cache(N);

	for (int i = 0; i <= N; i++)
	{
	    std::cout << "got " << cache.count(i) << " positions." << std::endl;
	}
}
