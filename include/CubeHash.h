
#ifndef CUBEHASH_H
#define CUBEHASH_H

#include "Cube.h"
#include "Enums.h"

namespace std {
    template<> struct hash<Cube>
    {

        std::size_t operator()(const Cube &cube) const
        {
            std::size_t result = 17;

            result = result * 31 + cube.cornerSlot(RUF).hash();
            result = result * 31 + cube.cornerSlot(LUF).hash();
            result = result * 31 + cube.cornerSlot(LUB).hash();
            result = result * 31 + cube.cornerSlot(RUB).hash();
            result = result * 31 + cube.cornerSlot(RDF).hash();
            result = result * 31 + cube.cornerSlot(LDF).hash();
            result = result * 31 + cube.cornerSlot(LDB).hash();
            result = result * 31 + cube.cornerSlot(RDB).hash();

            result = result * 31 + cube.edgeSlot(RU).hash();
            result = result * 31 + cube.edgeSlot(UF).hash();
            result = result * 31 + cube.edgeSlot(LU).hash();
            result = result * 31 + cube.edgeSlot(UB).hash();
            result = result * 31 + cube.edgeSlot(RF).hash();
            result = result * 31 + cube.edgeSlot(LF).hash();
            result = result * 31 + cube.edgeSlot(LB).hash();
            result = result * 31 + cube.edgeSlot(RB).hash();
            result = result * 31 + cube.edgeSlot(RD).hash();
            result = result * 31 + cube.edgeSlot(DF).hash();
            result = result * 31 + cube.edgeSlot(LD).hash();
            result = result * 31 + cube.edgeSlot(DB).hash();

            return result;
        }
    };
}

#endif
