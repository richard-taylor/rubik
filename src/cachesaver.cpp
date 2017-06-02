
#include <iostream>
#include "CacheBuilder.h"
#include "CubePacker.h"
#include "OrientPacker.h"
#include "UnorderedMapCache.h"

void cube_cache()
{
    CubePacker packer;
    UnorderedMapCache cubes(packer.state_bits());
    
    CacheBuilder cacheBuilder(cubes, packer);
    cacheBuilder.verbose(true);
    cacheBuilder.build(6);
	
    cubes.save("cubes-cache-6.binary");
	
    std::cout << "saved cube positions = " << cubes.count() << std::endl;
}

void orient_cache()
{
    OrientPacker packer;
    UnorderedMapCache orients(packer.state_bits());
    
    CacheBuilder cacheBuilder(orients, packer);
    cacheBuilder.verbose(true);
    cacheBuilder.build(12);
	
    orients.save("orients-cache-12.binary");
	
    std::cout << "saved orients positions = " << orients.count() << std::endl;
}

int main()
{
    //cube_cache();
    orient_cache();
}
