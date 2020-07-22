
#include <stdexcept>
#include "EOLine.h"
#include "Cube.h"

bool EOLine::on(const Cube &cube) const
{
    return cube.edgeSolved(DF) && cube.edgeSolved(DB) &&
      cube.edgeSlot(RU).isOriented(Z) &&
      cube.edgeSlot(UF).isOriented(Z) &&
      cube.edgeSlot(LU).isOriented(Z) &&
      cube.edgeSlot(UB).isOriented(Z) &&
      cube.edgeSlot(RF).isOriented(Z) &&
      cube.edgeSlot(LF).isOriented(Z) &&
      cube.edgeSlot(LB).isOriented(Z) &&
      cube.edgeSlot(RB).isOriented(Z) &&
      cube.edgeSlot(RD).isOriented(Z) &&
      cube.edgeSlot(LD).isOriented(Z);
}
