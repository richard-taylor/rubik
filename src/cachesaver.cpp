
#include <iostream>
#include "CacheBuilder.h"
#include "CubePacker.h"
#include "UnorderedMapCache.h"

void cube_cache()
{
    CubePacker packer;
    UnorderedMapCache cubes(packer.state_bits());
    
	CacheBuilder cubeCacheBuilder(cubes, packer);
	cubeCacheBuilder.verbose(true);
	cubeCacheBuilder.build(6);
	
	cubes.save("cubes-cache-6.binary");
	
	std::cout << "saved cube positions = " << cubes.count() << std::endl;
}

int main()
{
    cube_cache();
}
