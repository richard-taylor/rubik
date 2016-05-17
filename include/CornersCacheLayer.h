
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
    
    /**
    Write a cube state to a binary stream.
    */
    static void write_state(std::ostream &out, const Cube &cube);
    
    /**
    Read a cube and its last twist from a binary stream.
    */
    static bool read_cube(std::istream &in, Cube &cube, Cube::Twist &twist);
    
    /**
    Write a cube and its last twist to a binary stream.
    */
    static bool write_cube(std::ostream &out, const Cube &cube, const Cube::Twist &twist);
    
    static int squash_states(const std::string &state_max, const std::string &statefile);
    static int squash_cubes(const std::string &cube_max, const std::string &cubefile);
    
private:
    std::vector<unsigned long long> m_vector;
};

#endif
