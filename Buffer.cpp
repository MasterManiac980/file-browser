#include <iostream>
#include <fstream>
#include <iomanip>

#include "Buffer.h"

void Buffer::display()
{
    for (size_t i = m_topLineNum; i < (m_topLineNum + m_viewableLines); i++)
    {
        std::cout << std::right << std::setw(3) << i + 1 << std::left << std::setw(3) << " " << m_bufferData[i] << std::endl;
    }
}

void Buffer::nextPage()
{
    m_topLineNum += m_viewableLines;
    display();
}

void Buffer::openLink(int linkNumber)
{
    m_bufferData.clear();
    readFile(m_fileNames[linkNumber]);
}

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
        while (!infile.eof())
        {
            infile >> currentLine;
            if (infile.eof()) break;
            if (currentLine == "<a") {
                std::string fileDescriptor = "<";
                infile >> fileDescriptor;
                infile >> m_fileNames.push_back();
            }
            else if {

            }
            else if {

            }
            m_bufferData.push_back(currentLine);
        }
    }
    infile.close();
}

void Buffer::setViewableArea(int verticalLines, int horizontalCharacters)
{
    m_viewableLines = verticalLines;
    m_charsPerLine = horizontalCharacters;
}
