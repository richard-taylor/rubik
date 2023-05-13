
#include <stdexcept>
#include "EO.h"
#include "Cube.h"

bool EO::on(const Cube &cube) const
{
    return (
      cube.edgeSlot(RU).isOriented(X) && cube.edgeSlot(UF).isOriented(X) &&
      cube.edgeSlot(LU).isOriented(X) && cube.edgeSlot(UB).isOriented(X) &&
      cube.edgeSlot(RF).isOriented(X) && cube.edgeSlot(LF).isOriented(X) &&
      cube.edgeSlot(LB).isOriented(X) && cube.edgeSlot(RB).isOriented(X) &&
      cube.edgeSlot(RD).isOriented(X) && cube.edgeSlot(DF).isOriented(X) && 
      cube.edgeSlot(LD).isOriented(X) && cube.edgeSlot(DB).isOriented(X)
      ) || (
      cube.edgeSlot(RU).isOriented(Y) && cube.edgeSlot(UF).isOriented(Y) &&
      cube.edgeSlot(LU).isOriented(Y) && cube.edgeSlot(UB).isOriented(Y) &&
      cube.edgeSlot(RF).isOriented(Y) && cube.edgeSlot(LF).isOriented(Y) &&
      cube.edgeSlot(LB).isOriented(Y) && cube.edgeSlot(RB).isOriented(Y) &&
      cube.edgeSlot(RD).isOriented(Y) && cube.edgeSlot(DF).isOriented(Y) && 
      cube.edgeSlot(LD).isOriented(Y) && cube.edgeSlot(DB).isOriented(Y)
      ) || (
      cube.edgeSlot(RU).isOriented(Z) && cube.edgeSlot(UF).isOriented(Z) &&
      cube.edgeSlot(LU).isOriented(Z) && cube.edgeSlot(UB).isOriented(Z) &&
      cube.edgeSlot(RF).isOriented(Z) && cube.edgeSlot(LF).isOriented(Z) &&
      cube.edgeSlot(LB).isOriented(Z) && cube.edgeSlot(RB).isOriented(Z) &&
      cube.edgeSlot(RD).isOriented(Z) && cube.edgeSlot(DF).isOriented(Z) && 
      cube.edgeSlot(LD).isOriented(Z) && cube.edgeSlot(DB).isOriented(Z)
      );
}
