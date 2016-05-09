
#include <cassert>
#include <stack>
#include <utility>
#include "Cache.h"
#include "Cube.h"

bool cant_follow(int last, int next)
{
    if (next == last)
        return true;

    switch (last)
    {
        case Cube::L : return false;
        case Cube::R : return (next == Cube::R);    // R cannot follow L
        case Cube::U : return false;
        case Cube::D : return (next == Cube::U);    // U cannot follow D
        case Cube::F : return false;
        case Cube::B : return (next == Cube::F);    // F cannot follow B
    }
    return false;
}
