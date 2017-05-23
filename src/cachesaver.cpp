
#include <iostream>
#include "CacheBuilder.h"
#include "CubePacker.h"
#include "TrieCache.h"

int main()
{
    CubePacker packer;
    TrieCache  cubes(packer.state_bits(), 10000000);
    
	CacheBuilder cubeCacheBuilder(cubes, packer);
	cubeCacheBuilder.verbose(true);
	cubeCacheBuilder.build(4);
	
	cubes.save("cache/cubes");
	std::cout << "saved positions = " << cubes.count() << std::endl;
	std::cout << "table size = " << cubes.table_used() << std::endl;
	std::cout << "table over = " << cubes.table_waste() << std::endl;
}
