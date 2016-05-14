
#ifndef CORNERSCACHELAYER_H
#define CORNERSCACHELAYER_H

#include <vector>
#include <string>

class Cube;

// implements LayerType for use in a Cache

class CornersCacheLayer
{
public:
    /**
    Load a layer of a certain depth (number of moves from solved).
    */
    CornersCacheLayer(const std::string &basename, int deep);
    
    /**
    Get the depth of the layer (number of moves from solved).
    */
    int depth() const;
    
    /**
    Count the number of states in this layer.
    */
    int size() const;
    
    /**
    Test for a cached cube state in this layer.
    */
    bool contains(const Cube &cube) const;
    
private:
    std::vector<unsigned long long> m_vector;
    int m_depth;
};

#endif
