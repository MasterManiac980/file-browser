#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include "Buffer.h"
#include "UI.H"

using namespace std; 
const string Short_Ast(10,'*');
const string Long_Ast(80,'*'); 

void execute(char selection, bool & done)
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
            if (! m_buffer.open(file_name)) m_buffer.error_message_ = "Could not open " + file_name;
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