#pragma once

#include "Buffer.h"

class UI
{
public:
    void run();

private:
    Buffer m_buffer;
    void display();
    void execute(char selection, bool &done);
    int m_viewableLines;
    std::string error_message_;
};