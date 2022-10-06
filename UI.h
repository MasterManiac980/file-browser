#pragma once

#include "Buffer.h"

class UI
{
public:

private:
    Buffer m_buffer;
    void display();
    void execute(char selection, bool & done);
    int m_viewableLines; 

    
};