#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include "Buffer.h"
#include "UI.H"

using namespace std; 
 

void UI::display()
{
    const string Short_Dash(10,'-');
    const string Long_Dash(80,'-');
    //Clear screen isn't working. Ask Cary. 

    //If there is an error message 
    m_buffer.printError();
    cout << Long_Dash << endl;
    m_buffer.display();
    cout << Long_Dash << endl;
    cout << "(O)pen (G)o (N)ext  (P)revious (Q)uit\n";
    cout << Short_Dash << endl;
}

void UI::execute(char selection, bool & isDone)
{
switch (selection) 
{
     
        case 'n': 
        {
            //Next page 
            m_buffer.nextPage();   
            break;
        }
        case 'g': 
        {
            //open link
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);

            int file_num;
            file_num = stoi(file_name);
            m_buffer.openLink(file_num);
            m_buffer.printError();
        }
        case 'o': 
        {
            //open file 
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);

            if(file_name.substr(0,1) != "<")
            {
                m_buffer.openFile(file_name);
            }

            break;
        }

        case 'p': 
        {
            //previous page
            m_buffer.openLastFile();
            break;
        }

        case 'q': 
        {
            //quit
            isDone = true;
            break;
        }
        default: 
        {

        }
    }
}

void UI::run()
{
    cout << "Enter Window Height: ";
    cin >> m_vertical_lines;
    cin.get();  // '\n'
    cout << '\n';
    cout <<"Enter Window Width: ";
    cin >> m_horizontal_lines;
    cin.get();  // '\n'
    cout << '\n';
    m_buffer.setViewableArea(m_vertical_lines,m_horizontal_lines);

    bool isDone = false;
    while (!isDone) 
    {
        display();
        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); 
        execute(command, isDone);

        cout << endl;
    }
}