
#include <iostream>
#include "CacheBuilder.h"
#include "UnorderedMapCache.h"

/*void cube_cache()
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
    cacheBuilder.keep_descending(true);
    cacheBuilder.build(6);

    orients.save("orients-cache-6.binary");

    std::cout << "saved orients positions = " << orients.count() << std::endl;
}*/

void half_cut_cache()
{
    //HalfCutPacker packer;
    //UnorderedMapCache cache(packer.state_bits());

    //CacheBuilder cacheBuilder(cache, packer);
    //cacheBuilder.verbose(true);
    //cacheBuilder.keep_descending(true);
    //cacheBuilder.build(9);

    //cache.save("half-cut-cache-6.binary");

    //std::cout << "saved positions = " << cache.count() << std::endl;
}

int main()
{
    //cube_cache();
    //orient_cache();
    half_cut_cache();
}
