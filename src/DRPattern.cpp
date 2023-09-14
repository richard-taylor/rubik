
#include <stdexcept>
#include "DR.h"
#include "Cube.h"

DR::DR(Axis axis)
{
    this->axis = axis;
}

bool dr_x(const Cube &cube)
{
    Edge uf = cube.edgeSlot(UF);
    Edge df = cube.edgeSlot(DF);
    Edge ub = cube.edgeSlot(UB);
    Edge db = cube.edgeSlot(DB);

    return uf.isOriented(Y) && uf.in(UF, DF, UB, DB) &&    // 4 equator edges
           df.isOriented(Y) && df.in(UF, DF, UB, DB) &&
           ub.isOriented(Y) && ub.in(UF, DF, UB, DB) &&
           db.isOriented(Y) && db.in(UF, DF, UB, DB) &&
           cube.cornerSlot(RUF).isOriented(X) &&           // 8 corners
           cube.cornerSlot(LUF).isOriented(X) &&
           cube.cornerSlot(LUB).isOriented(X) &&
           cube.cornerSlot(RUB).isOriented(X) &&
           cube.cornerSlot(RDF).isOriented(X) &&
           cube.cornerSlot(LDF).isOriented(X) &&
           cube.cornerSlot(LDB).isOriented(X) &&
           cube.cornerSlot(RDB).isOriented(X) &&
           cube.edgeSlot(RU).isOriented(Y) &&              // 8 non-equator edges
           cube.edgeSlot(LU).isOriented(Y) &&
           cube.edgeSlot(RF).isOriented(Y) &&
           cube.edgeSlot(LF).isOriented(Y) &&
           cube.edgeSlot(LB).isOriented(Y) &&
           cube.edgeSlot(RB).isOriented(Y) &&
           cube.edgeSlot(RD).isOriented(Y) &&
           cube.edgeSlot(LD).isOriented(Y);
}

bool dr_y(const Cube &cube)
{
    Edge lf = cube.edgeSlot(LF);
    Edge rf = cube.edgeSlot(RF);
    Edge lb = cube.edgeSlot(LB);
    Edge rb = cube.edgeSlot(RB);

    return lf.isOriented(Z) && lf.in(LF, RF, LB, RB) &&    // 4 equator edges
           rf.isOriented(Z) && rf.in(LF, RF, LB, RB) &&
           lb.isOriented(Z) && lb.in(LF, RF, LB, RB) &&
           rb.isOriented(Z) && rb.in(LF, RF, LB, RB) &&
           cube.cornerSlot(RUF).isOriented(Y) &&           // 8 corners
           cube.cornerSlot(LUF).isOriented(Y) &&
           cube.cornerSlot(LUB).isOriented(Y) &&
           cube.cornerSlot(RUB).isOriented(Y) &&
           cube.cornerSlot(RDF).isOriented(Y) &&
           cube.cornerSlot(LDF).isOriented(Y) &&
           cube.cornerSlot(LDB).isOriented(Y) &&
           cube.cornerSlot(RDB).isOriented(Y) &&
           cube.edgeSlot(RU).isOriented(Z) &&              // 8 non-equator edges
           cube.edgeSlot(UF).isOriented(Z) &&
           cube.edgeSlot(LU).isOriented(Z) &&
           cube.edgeSlot(UB).isOriented(Z) &&
           cube.edgeSlot(RD).isOriented(Z) &&
           cube.edgeSlot(DF).isOriented(Z) &&
           cube.edgeSlot(LD).isOriented(Z) &&
           cube.edgeSlot(DB).isOriented(Z);
}

bool dr_z(const Cube &cube)
{
    Edge ld = cube.edgeSlot(LD);
    Edge rd = cube.edgeSlot(RD);
    Edge lu = cube.edgeSlot(LU);
    Edge ru = cube.edgeSlot(RU);

    return ld.isOriented(X) && ld.in(LD, RD, LU, RU) &&    // 4 equator edges
           rd.isOriented(X) && rd.in(LD, RD, LU, RU) &&
           lu.isOriented(X) && lu.in(LD, RD, LU, RU) &&
           ru.isOriented(X) && ru.in(LD, RD, LU, RU) &&
           cube.cornerSlot(RUF).isOriented(Z) &&           // 8 corners
           cube.cornerSlot(LUF).isOriented(Z) &&
           cube.cornerSlot(LUB).isOriented(Z) &&
           cube.cornerSlot(RUB).isOriented(Z) &&
           cube.cornerSlot(RDF).isOriented(Z) &&
           cube.cornerSlot(LDF).isOriented(Z) &&
           cube.cornerSlot(LDB).isOriented(Z) &&
           cube.cornerSlot(RDB).isOriented(Z) &&
           cube.edgeSlot(UF).isOriented(X) &&              // 8 non-equator edges
           cube.edgeSlot(UB).isOriented(X) &&
           cube.edgeSlot(RF).isOriented(X) &&
           cube.edgeSlot(LF).isOriented(X) &&
           cube.edgeSlot(LB).isOriented(X) &&
           cube.edgeSlot(RB).isOriented(X) &&
           cube.edgeSlot(DF).isOriented(X) &&
           cube.edgeSlot(DB).isOriented(X);
}

bool DR::on(const Cube &cube) const
{
    switch (axis)
    {
        case Axis::X:
            return dr_x(cube);
        case Axis::Y:
            return dr_y(cube);
        case Axis::Z:
            return dr_z(cube);
    }
}
