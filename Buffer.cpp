#include <iostream>
#include <fstream>
#include <iomanip>

#include "Buffer.h"

void Buffer::display()
{
}

void Buffer::nextPage()
{
    m_topLineNum += m_viewableLines;
}

void Buffer::openLast() {
    readFile(m_history[m_history.size() - 1]);
    m_history.erase(m_history.begin() + (m_history.size() - 1));
}

void Buffer::openLink(int linkNumber)
{
    linkNumber -= 1; // Converts number provided to index for accessing file name in vector
    m_bufferData.clear();
    m_history.push_back(m_currentFileName);
    readFile(m_fileNames[linkNumber]);
}

void Buffer::readFile(std::string fileName)
/*

    TODO: Modify the input based on the tags provided in the text

    1. Look for < in each line
    2. After each <, take use >> to take in the tag type
    3. Use if statement(?) to change functionality based on tag type,
        a. br: insert line break character
        b. p: insert two line break characters to create a blank line
        c. a: take in next two strings using >> and modify text presented to match

*/
{
    
    std::ifstream infile(fileName);
    if (!infile.fail())
    {
        m_currentFileName = fileName;
    }
    else
    {
        
        return;
    }
    infile.close();
}

void Buffer::setViewableArea(int verticalLines, int horizontalCharacters)
{
    m_viewableLines = verticalLines;
    m_charsPerLine = horizontalCharacters;
}
