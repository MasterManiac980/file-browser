#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include "Buffer.h"
#include "UI.H"

using namespace std; 
const string Short_Ast(10,'*');
const string Long_Ast(80,'*'); 

void UI::run()
{
    cout << "Enter Window Height: ";
    cin >> m_viewableLines;
    cin.get();  // '\n'
    cout << '\n';
    m_buffer.setViewableArea(m_viewableLines);

    bool done = false;
    while (!done) {
        display();
        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); 
        execute(command, done);

        cout << endl;
    }
void UI::execute(char selection, bool & done)
{
switch (selection) {
     
        case 'n': {
            //Next page 
            m_buffer.nextPage();   
            break;
        }

        case 'o': {
            //open file 
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);
            m_buffer.openFile(file_name);
            break;
        }

        case 'p': {
            //previous page
            break;
        }

        case 'q': {
            //quit
            break;
        }
    }
}