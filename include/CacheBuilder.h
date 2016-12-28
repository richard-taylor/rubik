
#ifndef CACHEBUILDER_H
#define CACHEBUILDER_H

#include <string>
#include <vector>

class Cube;

template <class LayerType> class CacheBuilder
{
public:
    /**
    Builder with a given basename.
    
    The layers will have ".1", ".2", ".3" etc appended to the basename.
    
    Some other intermediate files are created too, all with the same basename.
    */
    CacheBuilder(const std::string &basename);

    /**
    To print messages on stdout or not? Default is no messages.
    */    
    void verbose(bool on);
    
    /**
    Is the builder currently set to print messages or not?
    */
    bool verbose() const;
    
    /**
    Build all layers up to and including the given depth.
    
    The files from previously created layers are reused to create new layers.
    */
    void build(int deep);
    
    /**
    Free all the memory used by the layers in this cache builder.
    
    Leaves all the generated files untouched.
    */
    void free();
    
private:
    std::string m_basename;
    bool m_verbose;
    std::vector<LayerType*> m_layers;
    
    int build_layer(int N);
    void new_layer(LayerType *layer);
    bool seen_before(const Cube &cube);
};
    
#include "CacheBuilder.impl"
#endif
