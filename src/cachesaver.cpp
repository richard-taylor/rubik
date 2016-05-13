
#include <iostream>
#include "CubeCache.h"
#include "CornersCache.h"

int main()
{
	/*CubeCache cubes(6);

	for (int i = 0; i <= cubes.depth(); i++)
	{
	    std::cout << "got " << cubes.count(i) << " cube positions." << std::endl;
	}*/
	
	CornersCache corners(7);
	
	for (int i = 0; i <= corners.depth(); i++)
	{
	    std::cout << "got " << corners.count(i) << " corner positions." << std::endl;
	}
}
