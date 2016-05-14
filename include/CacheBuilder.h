
#ifndef CACHEBUILDER_H
#define CACHEBUILDER_H

#include <string>
#include <vector>

/**
Build a cache with a given basename, up to a maximum depth.
    
The layers will have ".1", ".2", ".3" etc appended to the basename.
    
If some layers already exist then they will be reused to make the
later layers.

Returns the total number of layers.
*/
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
    
private:
    std::string m_basename;
    bool m_verbose;
    std::vector<LayerType> m_layers;
    
    std::string append(int N, std::string suffix = "");
    int build_layer(int N);
};
    
#include "CacheBuilder.impl"
#endif
