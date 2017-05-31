
#include <cassert>
#include <cstdlib>
#include <sstream>
#include "Scramble.h"

typedef std::vector<Cube::Twist>::const_iterator const_it;
typedef std::vector<Cube::Twist>::const_reverse_iterator const_ti;

Scramble::Scramble()
{
}

Scramble::Scramble(int length)
{
    int previous = -1;
    int next;
    
    for (int i = 0; i < length; ++i)
    {
        while ((next = rand() % 6) == previous)
        {
        }
        add(Cube::Twist((Cube::Face)next, rand() % 3 + 1));
        previous = next;
    }
}

int Scramble::length() const
{
    return twists.size();
}

void Scramble::add(Cube::Twist twist)
{
    twists.push_back(twist);
}

bool Scramble::can_add(Cube::Face face) const
{
    if (twists.size() == 0)
        return true;
        
    Cube::Face previous = last().getFace();
    
    if (face == previous)
        return false;

    switch (previous)
    {
        case Cube::L : return true;
        case Cube::R : return (face != Cube::L);    // L cannot follow R
        case Cube::U : return true;
        case Cube::D : return (face != Cube::U);    // U cannot follow D
        case Cube::F : return true;
        case Cube::B : return (face != Cube::F);    // F cannot follow B
    }
    return false;
}
    
void Scramble::apply(Cube &cube) const
{
    for (const_it i = twists.begin(); i != twists.end(); ++i)
    {
        cube.twist(*i);
    }
}

Cube Scramble::of(const Cube &cube) const
{
    Cube copy = cube;
    apply(copy);
    return copy;
}

Cube::Twist Scramble::last() const
{
    return twists.size() > 0 ? twists.back() : Cube::Twist();
}

Scramble Scramble::inverse() const
{
    Scramble inv;
    
    for (const_ti i = twists.rbegin(); i != twists.rend(); ++i)
    {
        inv.add(i->inverse());
    }
    return inv;
}

void Scramble::append(const Scramble &other)
{
    twists.insert(twists.end(), other.twists.begin(), other.twists.end());
}

std::string Scramble::toString() const
{
    std::stringstream str;
    
    for (const_it i = twists.begin(); i != twists.end(); ++i)
    {
        if (i != twists.begin())
            str << " ";
            
        switch (i->getFace())
        {
            case Cube::L : str << "L"; break;
            case Cube::R : str << "R"; break;
            case Cube::U : str << "U"; break;
            case Cube::D : str << "D"; break;
            case Cube::F : str << "F"; break;
            case Cube::B : str << "B"; break;
        }
        switch (i->getTurns())
        {
            case 2: str << "2"; break;
            case 3: str << "'"; break;
        }
    }
    
    return str.str();
}

bool Scramble::equivalent(const Scramble &other) const
{
    Cube a;
    apply(a);
    
    Cube b;
    other.apply(b);
    
    return (a == b);    // equivalent if both scramble to the same position
}

bool Scramble::read(std::istream &in, int length)
{
    Cube::Twist next;
    twists.clear();
    for (int i = 0; i < length; i++)
    {
        in.read((char*)&next, sizeof(Cube::Twist));
        twists.push_back(next);
    }
    return !in.eof() && in.good();
}

bool Scramble::write(std::ostream &out) const
{
    for (unsigned int i = 0; i < twists.size(); i++)
    {
        out.write((char*)&twists[i], sizeof(Cube::Twist));
    }
    return out.good();
}
