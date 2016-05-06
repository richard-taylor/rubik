
#include <iostream>
#include "Cache.h"

int main()
{
	Cache cache;

	for (int i = 1; i < 7; i++)
	{
	    std::cout << "Extending cache to depth " << i << " ... ";
	    cache.extend(i);
	    std::cout << "got " << cache.count(i) << " positions." << std::endl;
	}
}
