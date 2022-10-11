#pragma once

#include <iostream>
#include <vector>
#include <string>

class Buffer
{
public:
    // For UI startup
    void setViewableArea(int verticalLines, int horizontalCharacters);

    // Functions for main UI run loop
    void display();

    // Functions for UI menu
    void nextPage();
    void openLastFile();
    void openLink(int linkNumber);
    void openFile(std::string fileName);

    // Error Reporting
    void printError(std::ostream& out = std::cout);
    void setUIError(std::string errorMessage);

private:
    std::vector<std::string> m_bufferData;
    std::vector<std::string> m_fileNames;
    std::vector<std::string> m_history;
    int m_topLineNum;
    int m_viewableLines;
    int m_charsPerLine;
    std::string m_currentFileName;
    std::string m_BufferErrorMessage;
    std::string m_UIErrorMessage;
};
