
#ifndef ENUMS_H
#define ENUMS_H

/**
Enumeration of the 6 faces of a cube.
*/
enum Face { LEFT, RIGHT, UP, DOWN, FRONT, BACK };

/**
Enumeration of the 3 cartesian axes of a cube.
*/
enum Axis { X, Y, Z };

/**
Enumeration of the 8 corner positions on a cube.
*/
enum CornerSlot { RUF, LUF, LUB, RUB, RDF, LDF, LDB, RDB };

/**
Enumeration of the 12 edge positions on a cube.
*/
enum EdgeSlot { RU, UF, LU, UB, RF, LF, LB, RB, RD, DF, LD, DB };

#endif
