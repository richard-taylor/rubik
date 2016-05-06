
#include <cassert>
#include "Cache.h"

Cache::Cache()
{
    // layer 0 is the solved cube
    layers.push_back(Layer());
    
    layers[0][Cube()] = Scramble();
}

int Cache::depth() const
{
    return layers.size() - 1;
}

int Cache::count(int deep)
{
    return layers[deep].size();
}

static bool cant_follow(int last, int next)
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

void Cache::next_layer(const Layer &previous, Layer &next)
{
    Layer::const_iterator it = previous.begin();
    
    while (it != previous.end())
    {
        const Cube &cube = it->first;
        const Scramble &scramble = it->second;
        
        int last = (scramble.length() > 0) ? scramble.last().getFace() : -1;
        
        for (int f = 0; f < 6; f++)
        {
            if (cant_follow(last, f))
                continue;
                
            for (int t = 1; t < 4; t++)
            {
                Cube::Twist twist((Cube::Face)f, t);
                
                Cube new_cube = cube;
                new_cube.twist(twist);
                
                if (!contains(new_cube))
                {
                    Scramble new_scramble = scramble;
                    new_scramble.add(twist);
                
                    next[new_cube] = new_scramble;
                }
            }
        }
        ++it;
    }
}

void Cache::extend(int deep)
{
    int d = depth();
    
    while(d < deep)
    {
        layers.push_back(Layer());
        
        next_layer(layers[d], layers[d + 1]);
        ++d;
    }
}
    
bool Cache::contains(const Cube &cube, int deep /* = -1 */) const
{
    if (deep < 0)
    {
        std::vector<Layer>::const_reverse_iterator it = layers.rbegin();
        
        while (it != layers.rend())
        {
            if (it->find(cube) != it->end())
            {
                return true;
            }
            ++it;
        }
        return false;
    }
    else
    {
        return (layers[deep].find(cube) != layers[deep].end());
    }
}
    
Scramble Cache::solution(const Cube &cube) const
{
    std::vector<Layer>::const_reverse_iterator it = layers.rbegin();
        
    while (it != layers.rend())
    {
        Layer::const_iterator found = it->find(cube);
        
        if (found != it->end())
        {
            return found->second.inverse();
        }
        ++it;
    }
    return Scramble();
}
