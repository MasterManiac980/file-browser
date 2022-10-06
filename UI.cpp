#include <iostream>
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
            break;
        }

        case 'o': {
            //open file 
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