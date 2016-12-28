
#ifndef CACHELAYER_H
#define CACHELAYER_H

#include <fstream>
#include <string>
#include <vector>
#include "Cube.h"
#include "Scramble.h"

// abstract base class for LayerType to use in a Cache

class CacheLayer
{
public:
    /**
    A layer of a certain depth (number of moves from solved).
    
    Each state stored in the layer is the same size (in bytes).
    */
    CacheLayer(const std::string &basename, int deep, int state_size);
    
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
        
    // support for CacheBuilder
    //
    virtual void initialise();
    virtual bool get_position(Cube &cube, Cube::Twist &twist);
    virtual bool add_position(const Cube &cube, const Cube::Twist &twist);
    virtual void finalise();

protected:
    virtual void extract_state(const Cube &cube, unsigned char *state) const = 0;
    
    // optional overrides
    virtual std::string name();
    
    // needed by finalise (loads from a filename returned by name())
    void load();
    
private:
    std::string m_basename;
    int m_depth;
    int m_states; // int is a placeholder for the new "set" type
    
    std::unique_ptr<std::ifstream> cubes;
    std::unique_ptr<std::ofstream> temp;
};

#endif
