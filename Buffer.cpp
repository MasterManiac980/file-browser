#include <iostream>
#include <fstream>
#include <iomanip>

#include "Buffer.h"

void Buffer::display()
{
    uint64_t currentLineNumber = m_topLineNum;
    if (!m_bufferData.empty())
    {
        for (currentLineNumber; currentLineNumber < (m_topLineNum + m_viewableLines); currentLineNumber++)
        {
            if ((currentLineNumber - 1) < m_bufferData.size())
            {
                std::cout << std::setw(3) << currentLineNumber << "  " << m_bufferData[currentLineNumber - 1] << std::endl;
            }
        }
    }
}

void Buffer::lastPage()
{
    if ((m_topLineNum - m_viewableLines) > 0)
    {
        m_topLineNum -= m_viewableLines;
    }
    else
    {
        m_topLineNum = m_bufferData.size() - (m_bufferData.size() % m_viewableLines);
    }
}

void Buffer::nextPage()
{
    if ((m_topLineNum + m_viewableLines) < m_bufferData.size())
    {
        m_topLineNum += m_viewableLines;
    }
    else
    {
        m_topLineNum = 1;
    }
}

void Buffer::openLastFile()
{
    if (!m_history.empty()) {
    openFile(m_history[m_history.size() - 1]);
    m_history.erase(m_history.begin() + (m_history.size() - 1));
    }
    else {
        m_BufferErrorMessage = "File history empty";
    }
}

void Buffer::openLink(uint32_t linkNumber)
{
    linkNumber -= 1; // Converts number provided to index for accessing file name in vector
    m_history.push_back(m_currentFileName);
    openFile(m_linkFileNames[linkNumber]);
}

void Buffer::printError(std::ostream &out)
// Only prints errors if there is one present, if the error message string is empty, nothing is done
{
    if (!m_BufferErrorMessage.empty())
    {
        out << "Buffer Error: " + m_BufferErrorMessage << std::endl;
        m_BufferErrorMessage.clear();
    }
    if (!m_UIErrorMessage.empty())
    {
        out << "UI Error: " + m_UIErrorMessage << std::endl;
        m_UIErrorMessage.clear();
    }
}

void Buffer::openFile(std::string fileName)
{
    std::ifstream infile(fileName);
    if (!infile.fail())
    {
        m_bufferData.clear(); // Makes sure the buffer is clear before reading a new file into it
        m_linkFileNames.clear(); // Makes sure there are no file names currently stored before reading in the new file

        m_topLineNum = 1; // sets the top line back to 1 so that the file is properly displayed next time the buffer is printed
        m_currentFileName = fileName; // file name stored for later use if go command is entered

        std::string currentWord;
        std::string currentLine;

        while (infile >> currentWord)
        {
            if (currentWord == "<a")
            {
                std::string fileName;

                infile >> fileName;
                infile >> currentWord;

                currentWord.erase(currentWord.begin() + (currentWord.size() - 1)); // removes '>' from the end of the file name
                m_linkFileNames.push_back(fileName);
                currentWord = "<" + currentWord + ">[" + std::to_string(m_linkFileNames.size()) + "]";
            }
            else if (currentWord == "<br>")
            {
                m_bufferData.push_back(currentLine);
                currentLine.clear();
                continue;
            }
            else if (currentWord == "<p>")
            {
                if (!currentLine.empty())
                {
                    m_bufferData.push_back(currentLine);
                    currentLine.clear();
                }
                m_bufferData.push_back(currentLine);
                continue;
            }

            if ((currentLine.size() + currentWord.size() + 1) < m_charsPerLine) 
            // Plus 1 because of the space character that is going to be added to separate the current word from the next one
            {
                if (infile.get() == '\n')
                {
                    currentLine += currentWord;
                    m_bufferData.push_back(currentLine);
                    currentLine.clear();
                    continue;
                }
                else
                {
                    currentLine += currentWord;
                    currentLine += " ";
                }
            }
            else
            {
                if (infile.get() == '\n')
                {
                    currentLine += currentWord;
                    m_bufferData.push_back(currentLine);
                    currentLine.clear();
                    continue;
                }
                else
                {
                    m_bufferData.push_back(currentLine);
                    currentLine.clear();
                    currentLine += currentWord;
                    currentLine += " ";
                }
            }
            if (infile.peek() == '	') // checks for tab character
            {
                currentLine.push_back('	');
            }
        }
        m_bufferData.push_back(currentLine); // if a file doesn't have a \n at the end of its last line, this pushes that line on to the data vector
        infile.close();
    }
    else
    {
        m_BufferErrorMessage = "File \"" + fileName + "\" failed to open.";
    }
}

void Buffer::setUIError(std::string errorMessage)
{
    m_UIErrorMessage = errorMessage;
}

void Buffer::setViewableArea(uint32_t verticalLines, uint32_t horizontalCharacters)
{
    m_viewableLines = verticalLines;
    m_charsPerLine = horizontalCharacters;
}
