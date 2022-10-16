#include <iostream>
#include <string>
#include <iomanip>
#include "Buffer.h"
#include "UI.h"

using namespace std;

void UI::display()
{
    const string Short_Dash(10, '-');
    const string Long_Dash(80, '-');

    // prints error if there is one
    m_buffer.printError();//Prints error if one exists 
    cout << m_buffer.currentFile() << endl; 
    cout << Long_Dash << endl
         << endl;
    m_buffer.display();
    cout << endl
         << Long_Dash << endl;
    cout << "-(O)pen -(G)o -(B)ack -(N)ext Page -(P)revious Page -(Q)uit\n";
    cout << Short_Dash << endl;
}

void UI::execute(char selection, bool &isDone)
{
    switch (selection)
    {
    case 'N':
    case 'n':
    {
        // Next page
        m_buffer.nextPage();
        break;
    }
    case 'G':
    case 'g':
    {
        // Go ---opens a link
        int linkNumber;
        cout << "Link Number: ";
        cin >> linkNumber;
        m_buffer.openLink(linkNumber);
        break;
    }
    case 'O':
    case 'o':
    {
        // open file
        cout << "File Name: ";
        string file_name;
        getline(cin, file_name);
        m_buffer.openFile(file_name);
        break;
    }
    case 'B':
    case 'b':
    {
        // last file
        m_buffer.openLastFile();
        break;
    }
    case 'P':
    case 'p':
    {
        // previous page
        m_buffer.lastPage();
        break;
    }
    case 'Q':
    case 'q':
    {
        // quit
        isDone = true;
        break;
    }
    default:
    {
        m_buffer.setUIError("Invalid command");
    }
    }
}

void UI::run()
{
    char command;
    std::cout << "\033c";
    std::cout << "Welcome to Tyler and Cary's File Browser!\n\n";
    

    cout << "Enter Window Height (Lines): ";
    cin >> m_vertical_lines;
    cout << "Enter Window Width (Characters Per Line): ";
    cin >> m_horizontal_lines;
    m_buffer.setViewableArea(m_vertical_lines, m_horizontal_lines);

    bool isDone = false;
    while (!isDone)
    {
        std::cout << "\033c"; // clears the terminal to allow for the next presentation of the UI
        display();
        cout << "Please Enter Command (One Character): ";
        cin >> command;
        cin.get();
        execute(command, isDone);
    }
}