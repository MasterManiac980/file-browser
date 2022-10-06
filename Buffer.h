#pragma once

#include <iostream>
#include <vector>
#include <string>

class Buffer
{
public:
    void display();
    void nextPage();
    void openLink(int linkNumber);
    void readFile(std::string fileName);
    void setViewableArea(int verticalLines, int horizontalCharacters);

private:
    std::vector<std::string> m_bufferData;
    std::vector<std::string> m_fileNames;
    std::vector<int> m_history;
    int m_topLineNum;
    int m_viewableLines;
    int m_charsPerLine;
};