
#include <iostream>
#include "CacheBuilder.h"
#include "CubePacker.h"
#include "TrieCache.h"

void cube_cache()
{
    CubePacker packer;
    TrieCache  cubes(packer.state_bits(), 6215194);
    
	CacheBuilder cubeCacheBuilder(cubes, packer);
	cubeCacheBuilder.verbose(true);
	cubeCacheBuilder.build(4);
	
	cubes.save("cubes-cache.binary");
	
	std::cout << "saved cube positions = " << cubes.count() << std::endl;
	std::cout << "table size = " << cubes.table_used() << std::endl;
	std::cout << "table over = " << cubes.table_waste() << std::endl;
}

int main()
{
    cube_cache();
}
