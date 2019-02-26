
#include "CubePattern.h"

bool CubePattern::search(const Cube &cube,
                         const Sequence &twists,
                         std::vector<Sequence> &results) const
{
    if (on(cube))
    {
        results.push_back(twists);
        return true;
    }
    return false;               
}
