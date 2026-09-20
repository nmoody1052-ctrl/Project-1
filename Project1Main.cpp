//Include
#include <iostream>
#include <fstream>
//End

//Headers
        //Here for resource managment
#include "resource.h"
#include "resources.h"
        //End
//End
using namespace std;

//Prints Header
void header(){
        cout<<
        "+-----------------------------------------------+\n"<<
        "|        Computer Science and Engieering        |\n"<<
        "|        CSCE 2110 - Computer Science __        |\n"<<
        "|                                               |\n"<<
        "|                                               |\n"<<
        "|  Nathan Moody NJM0184 NathanMoody@my.unt.edu  |\n"<<
        "+-----------------------------------------------+\n\n";
}
//End

//Prints Menu
void menu(){
        cout<<
        "*********************** Menu **********************\n"<<
        "| 1.                                              |\n"<<
        "***************************************************\n"<<
        ">> ";

}
//End

int main(){
        //Vars
        string sVar;
        bool bVar;
        resources res;
        //End
        
        //Print Header
        header();
        //End
        
        //Load From Files
        ifstream res("resources.txt");
        //End
        
        //output menu
        return 0;
}
