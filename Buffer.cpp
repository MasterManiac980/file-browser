#include <iostream>
#include <fstream>
#include <iomanip>

#include "Buffer.h"

void Buffer::display()
{
    int lineCharCount;
    std::size_t lineNumber = 1;
    bool fitsInLine;

    std::cout << std::setw(3) << lineNumber << "  "; // Prints first line number
    for (std::string &word : m_bufferData)
    {
        fitsInLine = (lineCharCount + word.size()) <= m_charsPerLine;

        if (!fitsInLine || word == "\n")
        {
            lineNumber = lineNumber + 1;
            std::cout << std::endl << std::setw(3) << lineNumber << "  ";
            continue;
        }
        else if (fitsInLine)
        {
            std::cout << word;
            continue;
        }
    }
}

void Buffer::nextPage()
{
    m_topLineNum += m_viewableLines;
}

void Buffer::openLast()
{
    openFile(m_history[m_history.size() - 1]);
    m_history.erase(m_history.begin() + (m_history.size() - 1));
}

void Buffer::openLink(int linkNumber)
{
    linkNumber -= 1; // Converts number provided to index for accessing file name in vector
    m_bufferData.clear();
    m_history.push_back(m_currentFileName);
    openFile(m_fileNames[linkNumber]);
}

void Buffer::printError(std::ostream &out)
{
    if (!m_errorMessage.empty()) {
    out << "Buffer Error: " + m_errorMessage << std::endl;
    }
    if (!m_UIErrorMessage.empty()) {
    out << "UI Error: " + m_UIErrorMessage<< std::endl;
    }
}

void Buffer::openFile(std::string fileName)
{
    std::ifstream infile(fileName);
    if (!infile.fail())
    {
        m_currentFileName = fileName;
        std::string currentWord;

        while (!infile.eof())
        {
            infile >> currentWord;

            if (infile.eof())
            {
                break;
            }

            if (currentWord == "<a")
            {
                std::string fileName;

                infile >> currentWord;
                infile >> fileName;

                fileName.erase(fileName.begin() + (fileName.size() - 1)); // removes '>' from the end of the file name
                m_fileNames.push_back(fileName);
                currentWord = "<" + currentWord + ">[" + std::to_string(m_fileNames.size()) + "]";
            }
            else if (currentWord == "<br>")
            {
                currentWord = "\n";
            }
            else if (currentWord == "<p>")
            {
                currentWord = "\n\n";
            }
            m_bufferData.push_back(currentWord);
        }
    }
    else
    {
        m_errorMessage = "File: " + fileName + " failed to open.";
        return;
    }
    infile.close();
}

void Buffer::setUIError(std::string errorMessage) {
    m_UIErrorMessage = errorMessage;
}

void Buffer::setViewableArea(int verticalLines, int horizontalCharacters)
{
    m_viewableLines = verticalLines;
    m_charsPerLine = horizontalCharacters;
}
