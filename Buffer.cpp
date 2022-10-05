#include <iostream>
#include <fstream>

#include "Buffer.h"

void Buffer::readFile(std::string fileName)
/* TODO: Modify the input based on the tags provided in the text

    1. Look for < in each line
    2. After each <, take use >> to take in the tag type
    3. Use if statement(?) to change functionality based on tag type,
        a. br: insert line break character
        b. p: insert two line break characters to create a blank line
        c. a: take in next two strings using >> and modify text presented to match 

*/
{
    std::ifstream infile(fileName);
    std::string currentLine;
    if (infile.is_open())
    {
        while (std::getline(infile, currentLine))
        {
            m_bufferData.push_back(currentLine);
        }
    }
    infile.close();
}

void Buffer::display()
{
}

void Buffer::setViewableArea(int verticalLines, int horizontalCharacters)
{
    m_viewableLines = verticalLines;
    m_charsPerLine = horizontalCharacters;
}

void Buffer::openLink(int linkNumber)
{
}