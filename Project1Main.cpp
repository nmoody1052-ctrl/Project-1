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
        "|        Computer Science and Engineering       |\n"<<
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
        "| 1. List Resources                                |\n"<<
		"| 2. Insert Reservation                            |\n"<<
		"| 3. Remove Reservation                            |\n"<<
		"| 4. Display Reservations                          |\n"<<
		"| 5. Display Waitlist                              |\n"<<
		"| 6. Restore Cancelations                          |\n"<<
		"| 7. Dispaly Cancelations                          |\n"<<
		"| 8. Exit                                          |\n"<<
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

	//Load Reservations From File
	//End

    //Switch case for outputing menu
	bool bVar = true;
	int inp;
	//Menu Loop
	while(bVar){
		menu();
		cin>>inp;
		//Switch-Case
		switch(inp){
			//List Resources
			case 1:
				res.PrintResources();
				break;
			//Insert Reservation
			case 2:
				break;
			//Remove Reservation 
			case 3:
				break;
			//Display Reservations
			case 4:
				break;
			//Display Waitlist
			case 5:
				break;
			//Restore Cancelations
			case 6:
				break;
			//Dispaly Cancelations
			case 7:
				break;
			//Exit
			case 8:
				cout<<"Thank you for using this program. Goodbye!\n";
                        	exit(0);
            default:
				cout<<"Error: Invalid selection. Enter a value between 1-8.\n\n";
                        	break;
		}
		//End
	}
	//End
	//End
    return 0;
}

