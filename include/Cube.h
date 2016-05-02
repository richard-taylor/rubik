
#ifndef CUBE_H
#define CUBE_H

class Cube
{
public:
    enum Face { L, R, U, D, F, B };
    
    /**
    Create a solved cube.
    */
    Cube();
    
    /**
    Test whether the cube is solved.
    */
    bool solved() const;
    
    /**
    Twist one face by a number of 90 degree steps.
    
    twist(L, 1) is a standard L turn.
    twist(L, 2) is a standard L2 turn.
    twist(L, 3) is a standard L' turn.
    */
    void twist(Face face, int turns);
    
    /**
    Test for cubes with equal positions.
    */
    bool operator==(const Cube &other) const;
    
    /**
    Test for cubes with different positions.
    */
    bool operator!=(const Cube &other) const;
    
    /**
    Test for cube ordering (used by std::set)
    */
    bool operator<(const Cube &other) const;

private:
    static const unsigned char SOLVED_STATE[];
    static const int STATE_SIZE = 14;
    
    unsigned char state[STATE_SIZE];
    void debug(const char *label);
};

#endif
