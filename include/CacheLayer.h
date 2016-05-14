
#ifndef CACHELAYER_H
#define CACHELAYER_H

#include <string>
#include <vector>

class Cube;

// abstract base class for LayerType to use in a Cache

class CacheLayer
{
public:
    /**
    A layer of a certain depth (number of moves from solved).
    */
    CacheLayer(int deep);
    
    /**
    Get the depth of the layer (number of moves from solved).
    */
    int depth() const;
    
    /**
    Count the number of states in this layer.
    */
    virtual int size() const = 0;
    
    /**
    Test for a cached cube state in this layer.
    */
    virtual bool contains(const Cube &cube) const = 0;
        
private:
    int m_depth;
};

#endif
