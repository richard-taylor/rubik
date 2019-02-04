
#include <stdexcept>
#include "Sequence.h"

Sequence::Sequence()
{
}

int Sequence::length() const
{
    return twists.size();
}

void Sequence::add(Twist twist)
{
    twists.push_back(twist);
}

bool Sequence::nextFace(Face face) const
{
    if (twists.size() == 0)
        return true;

    Face previous = last().getFace();

    if (face == previous)
        return false;

    switch (previous)
    {
        case LEFT:  return true;
        case RIGHT: return (face != LEFT);  // L cannot follow R
        case UP:    return true;
        case DOWN:  return (face != UP);    // U cannot follow D
        case FRONT: return true;
        case BACK:  return (face != FRONT); // F cannot follow B
    }
    return false;
}

Twist Sequence::last() const
{
    if (length() > 0)
        return twists.back();
    else
        throw std::out_of_range("An empty sequence has no 'last' twist.");
}

Sequence Sequence::inverse() const
{
    Sequence inv;

    for (auto t = twists.rbegin(); t != twists.rend(); ++t)
    {
        inv.add(t->inverse());
    }
    return inv;
}

void Sequence::append(const Sequence &other)
{
    twists.insert(twists.end(), other.twists.begin(), other.twists.end());
}

Sequence::const_iterator Sequence::begin() const
{
    return twists.begin();
}

Sequence::const_iterator Sequence::end() const
{
    return twists.end();
}
