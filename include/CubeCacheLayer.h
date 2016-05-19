
#ifndef CUBECACHELAYER_H
#define CUBECACHELAYER_H

#include <string>
#include <vector>
#include "CacheLayer.h"
#include "Cube.h"
#include "Scramble.h"

// implements LayerType for use in a Cache

class CubeCacheLayer : public CacheLayer
{
public:
    /**
    Load a layer of a certain depth (number of moves from solved).
    */
    CubeCacheLayer(const std::string &basename, int deep);
    
    /**
    Count the number of states in this layer.
    */
    int size() const;
    
    /**
    Test for a cached cube state in this layer.
    */
    bool contains(const Cube &cube) const;
    
    /**
    Retrieve the solution for a given cube state.
    */
    Scramble solution(const Cube &cube) const;
    
    // stuff for the CacheBuilder
    
    class Position
    {
    public:
        Cube cube() const;
        Cube::Twist lastTwist() const;
        
        bool operator<(const Position &other) const;

    private:
        Cube m_cube;
        Scramble m_scramble;
    
        friend class CubeCacheLayer;
    };
    
    static bool exists(const std::string &basename, int deep);
    static int make_first_layer(const std::string &basename);
    static std::string temp_file(const std::string &basename, int deep);
    static std::string cube_file(const std::string &basename, int deep);
    static bool read_position(std::istream &in, Position &position);
    static bool write_position(std::ostream &out, const Position &position, const Cube &next_cube, const Cube::Twist &next_twist);
    static int squash_temp(const std::string &basename, int deep);
    
private:
    std::vector<Position> m_vector;
    int m_depth;
};

#endif
