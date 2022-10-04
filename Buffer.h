#include <iostream>
#include <vector>
#include <string>

class Buffer
{
public:
    void display();

private:
    std::vector<std::string> m_bufferData;
};