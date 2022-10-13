#include <iostream>
#include <fstream>
#include <iomanip>

#include "Buffer.h"

void Buffer::display()
{
    uint16_t lineCharCount = 0;
    uint64_t currentLineNumber = m_topLineNum;
    bool fitsOnLine;
    static uint64_t nextWordToPrint = 0;

    if ((((currentLineNumber - 1) % m_viewableLines) == 0) && (nextWordToPrint < m_bufferData.size()))
    // makes sure that there is a line number when the first line and next / previous page is printed
    {
        std::cout << std::endl
                  << std::setw(3) << currentLineNumber << "  ";
        if (m_bufferData[nextWordToPrint] == "\n")
        {
            m_bufferData.erase(m_bufferData.begin() + nextWordToPrint);
        }
    }

    for (nextWordToPrint; nextWordToPrint < m_bufferData.size(); nextWordToPrint++)
    {
        fitsOnLine = (lineCharCount += (m_bufferData[nextWordToPrint].size() + 1)) <= m_charsPerLine;
        // 1 is added to the size because of the space added to the end of the word

        if (!fitsOnLine || (m_bufferData[nextWordToPrint] == "\n"))
        // If the next word won't fit on the current line or if the next word is a newline character, skips to the next line before printing
        {
            if (!fitsOnLine)
            {
                nextWordToPrint--; // Makes sure that the current word will still print as long as a newline character was not the cause of entrance into the conditional
            }
            if ((currentLineNumber) == (m_viewableLines + m_topLineNum - 1)) // 1 is subtracted because the first line is line 1
            {
                break; // Breaks out of for loop to stop printing words if the line limit has been reached
            }
            std::cout << std::endl
                      << std::setw(3) << (currentLineNumber += 1) << "  "; // Prints out the next line number when the line character limit has been reached
            lineCharCount = 0;                                             // Sets the char count for the new line back to zero
        }
        else if (fitsOnLine)
        {
            std::cout << m_bufferData[nextWordToPrint] << " ";
        }
    }
}

void Buffer::lastPage()
{
    if ((m_topLineNum - m_viewableLines) < 1)
    {
        m_topLineNum -= m_viewableLines;
    }
    else
    {
        m_BufferErrorMessage = "No previous page.";
    }
}

void Buffer::nextPage()
{
    m_topLineNum += m_viewableLines;
}

void Buffer::openLastFile()
{
    openFile(m_history[m_history.size() - 1]);
    m_history.erase(m_history.begin() + (m_history.size() - 1));
}

void Buffer::openLink(uint32_t linkNumber)
{
    linkNumber -= 1; // Converts number provided to index for accessing file name in vector
    m_bufferData.clear();
    m_history.push_back(m_currentFileName);
    openFile(m_fileNames[linkNumber]);
}

void Buffer::printError(std::ostream &out)
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
        m_currentFileName = fileName;
        std::string currentWord;

        while (infile >> currentWord)
        {
            if (currentWord == "<a")
            {
                std::string fileName;

                infile >> fileName;
                infile >> currentWord;

                currentWord.erase(currentWord.begin() + (currentWord.size() - 1)); // removes '>' from the end of the file name
                m_fileNames.push_back(fileName);
                currentWord = "<" + currentWord + ">[" + std::to_string(m_fileNames.size()) + "]";
            }
            else if (currentWord == "<br>")
            {
                currentWord = "\n";
            }
            else if (currentWord == "<p>")
            {
                if (m_bufferData[m_bufferData.size() - 1] != "\n")
                // checks to make sure there isn't a newline character before the <p> tag
                {
                    m_bufferData.push_back("\n");
                }
                m_bufferData.push_back("\n");
                continue;
            }
            m_bufferData.push_back(currentWord);

            if (infile.get() == '\n')
            {
                m_bufferData.push_back("\n");
            }
            if (infile.peek() == static_cast<char>(9)) // Tab Character
            {
                m_bufferData.push_back("	");
            }
        }
    }
    else
    {
        m_BufferErrorMessage = "File \"" + fileName + "\" failed to open.";
        return;
    }
    infile.close();
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
