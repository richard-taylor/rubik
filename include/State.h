
#ifndef STATE_H
#define STATE_H

typedef unsigned char byte;

class State
{
public:
    State(int bits);
    ~State();
    
private:
    int m_bits;
    byte *m_bytes;
};

#endif
