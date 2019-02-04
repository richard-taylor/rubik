
#include <cassert>
#include <stdexcept>
#include "Sequence.h"

int main()
{
    Sequence empty;
    assert(empty.length() == 0);
    try {
        empty.last();
        assert(false);
    }
    catch (const std::out_of_range &e) {
        // expected result of calling last() on an empty sequence'
    }

    Sequence seq;
    seq.add(R);
    seq.add(U);
    seq.add(F);
    assert(seq.length() == 3);

    Sequence unique;
    unique.add(B2);
    assert(true == unique.nextFace(LEFT));
    assert(true == unique.nextFace(RIGHT));
    assert(true == unique.nextFace(UP));
    assert(true == unique.nextFace(DOWN));
    assert(false == unique.nextFace(BACK));
    assert(false == unique.nextFace(FRONT));

    Sequence two;
    two.add(L);
    two.add(R);
    assert(R == two.last());

    Sequence inv = two.inverse();
    assert(inv.length() == 2);

    Sequence::const_iterator it = inv.begin();
    assert(*(it++) == Ri);
    assert(*(it++) == Li);
    assert(it == inv.end());

    Sequence longer;
    assert(longer.length() == 0);
    longer.append(two);
    assert(longer.length() == 2);
    assert(longer.last() == R);
    longer.append(seq);
    assert(longer.length() == 5);
    assert(longer.last() == F);
}
