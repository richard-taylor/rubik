
#ifndef CORNERSCACHELAYER_H
#define CORNERSCACHELAYER_H

#include <fstream>
#include "CacheLayer.h"
#include "Cube.h"

// implements LayerType for use in a Cache

class CornersCacheLayer : public CacheLayer
{
public:
    /**
    Load a layer of a certain depth (number of moves from solved).
    */
    CornersCacheLayer(const std::string &basename, int deep);
    
    /**
    Count the number of states in this layer.
    */
    int size() const;
    
    /**
    Test for a cached cube state in this layer.
    */
    bool contains(const Cube &cube) const;
    
    // stuff for the CacheBuilder
    
    class Position
    {
    public:
        Cube cube() const;
        Cube::Twist lastTwist() const;
        
        bool operator<(const Position &other) const;

    private:
        Cube m_cube;
        Cube::Twist m_twist;
    
        friend class CornersCacheLayer;
    };
    
    static bool write_corners(std::ostream &out, unsigned long long corners);
    
    static bool exists(const std::string &basename, int deep);
    static int make_first_layer(const std::string &basename);
    static std::string temp_file(const std::string &basename, int deep);
    static std::string cube_file(const std::string &basename, int deep);
    static bool read_position(std::istream &in, Position &position, int deep);
    static bool write_position(std::ostream &out, const Position &position, const Cube &next_cube, const Cube::Twist &next_twist);
    static int squash_temp(const std::string &basename, int deep);
    
private:
    std::vector<unsigned long long> m_vector;
};

#endif
