#include <iostream>
#include "global_variables.h"
using namespace std;

//double drawing_board_b, drawing_board_l;

//not used as of now.
void convert_drawing_resolution(string units)  //asks for and converts to millimeters
{
        if(units=="cm")
        {
            drawing_board_l*=10;
            drawing_board_b*=10;
        }
        else if(units=="mm")
        {
            drawing_board_l*=1;
            drawing_board_b*=1;
        }
        else if(units=="inches")
        {
            drawing_board_l*=25.4;
            drawing_board_b*=25.4;
        }
        cin.ignore(10000,'\n');
}

