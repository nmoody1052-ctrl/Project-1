//Include
#include <iostream>
#include <fstream>
#include <sstream>
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
        Resources res;
        int lineNum = 0;
        string line;
        //End
        
        //Print Header
        header();
        //End
        
	//Load From Files
	ifstream fileRes("resources.txt");

	if(!fileRes.is_open()){
		cout << "Error: Unable to open resources.txt\n\n";
		return 1;
	}

	while(getline(fileRes, line)){
		lineNum++;

		if(!line.empty() && line.back() == '\r') line.pop_back();
		if(line.empty()) continue;

		stringstream ss(line);
		string id, name, type, status;

		if(!getline(ss, id, '|') ||
		   !getline(ss, name, '|') ||
		   !getline(ss, type, '|') ||
		   !getline(ss, status)){
			cout << "Line " << lineNum << " skipped: missing field\n";
			continue;
		}

		Resource r;
		r.setID(id);
		r.setName(name);
		r.setType(type);
		r.setAvail(status);
		res.addResource(r);
	}

	fileRes.close();
	cout << res.getCount() << " resources loaded.\n\n";
	//End

	res.PrintResources();
        
    //output menu
    return 0;
}
