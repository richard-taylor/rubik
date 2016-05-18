
#include <iostream>
#include "CacheBuilder.h"
#include "CornersCacheLayer.h"

int main()
{
	/*CubeCache cubes(6);

	for (int i = 0; i <= cubes.depth(); i++)
	{
	    std::cout << "got " << cubes.count(i) << " cube positions." << std::endl;
	}*/
	
	CacheBuilder<CornersCacheLayer> corners("tmp_corners");
	corners.verbose(true);
	corners.build(11);
}
