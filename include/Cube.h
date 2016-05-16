
#ifndef CUBE_H
#define CUBE_H

class Cube
{
public:
    enum Face { L, R, U, D, F, B };

    /**
    Nested class to represent turning a face by 1, 2 or 3 lots of 90 degrees.
    
    This is the standard outer-block metric.
    */    
    class Twist
    {
    public:
        Twist(Face face, int turns);
        
        Face getFace() const;
        int getTurns() const;
        
        Twist inverse() const;
        bool operator==(const Twist &other) const;
        
    private:
        unsigned char twist;
    };

    /**
    Create a solved cube.
    */
    Cube();
    
    /**
    Test whether the cube is solved.
    */
    bool solved() const;
    
    /**
    Make a single move (in outer-block metric terms).
    */
    void twist(Twist turn);
    
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

    /**
    Get a 64-bit binary value representing the state of the cube's corners.
    
    The format of the representation should not be relied on. Only that two
    cubes with the same corner positions and orientations will return the
    same value; and two cubes with different corner positions or orientations
    will return different values.
    */
    unsigned long long corner_bits() const;
    
private:
    static const unsigned char SOLVED_STATE[];
    static const int STATE_SIZE = 14;
    
    unsigned char state[STATE_SIZE];
    void debug(const char *label);
};

#endif
