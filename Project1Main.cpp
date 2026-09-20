#include <iostream>
#include <fstream>
#include <sstream>
//End

//Headers
        //Here for resource managment
#include "resource.h"
#include "resources.h"
#include "reservation.h"
#include "ReservationList.h"
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
			//Resources class
        Resources res;
        int lineNum = 0;
        string line;
		string id, name, type, status;

		int studId, revId;
		string resIdStr, studIdStr, resName, resourceId, date;
		ReservationList reservation;

		bool bVar = true;
		int inp;

		int nextRevID = 0;
        //End
        
        //Print Header
        header();
        //End
        
	//Load RESORUCES From Files
	ifstream fileRes("resources.txt");

	if(!fileRes.is_open()){
		cout << "Error: Unable to open resources.txt\n\n";
		return 1;
	}

	while(getline(fileRes, line)){
		lineNum++;

		//Remove Windows \r and skip blank lines
		if(!line.empty() && line.back() == '\r') line.pop_back();
		if(line.empty()) continue;

		//Lets us split the line on '|'
		stringstream ss(line);

		//Split line on '|', skip line if a field is missing
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

	lineNum = 0;

	//Load Reservations From File
	ifstream fileVations("reservations.txt");

	if(!fileVations.is_open()){
		cout << "Error: Unable to open reservations.txt\n\n";
	}

	while(getline(fileVations, line)){
	lineNum++;

	//Remove Windows \r and skip blank lines
	if(!line.empty() && line.back() == '\r') line.pop_back();
	if(line.empty()) continue;

	//Lets us split the line on '|'
	stringstream ss(line);

	//Split line on '|', skip line if a field is missing
	if(!getline(ss, resIdStr, '|') ||
		!getline(ss, studIdStr, '|') ||
		!getline(ss, resName, '|') ||
		!getline(ss, resourceId, '|') ||
		!getline(ss, date)){
		cout << "Line " << lineNum << " skipped: missing field\n";
		continue;
	}

	//Convert IDs to numbers, skip line if not numbers
	try{
		revId = stoi(resIdStr);
		studId = stoi(studIdStr);
	}
	catch(...){
		cout << "Line " << lineNum << " skipped: bad number\n";
		continue;
	}

	//Track the highest ID for new reservations
	if(revId > nextRevID) nextRevID = revId;

	Reservation r(revId, studId, resourceId, resName, date);
	reservation.insertReservation(r);
	//End
	}

	fileVations.close();
	cout << lineNum << " reservations loaded.\n\n";

    //Switch case for outputing menu
	//Menu Loop
	while(bVar){
		menu();
		cin>>inp;
		//Switch-Case
		switch(inp){
			//List Resources
			case 1:{
				res.PrintResources();
				break;
			}
			//Insert Reservation NEED TO ADD WAITLIST FUNCTIONALITY
			case 2:{
				cout<<"Enter Resource ID :";
				cin>>id;

				//Look up the resource
				Resource* found = res.findResource(id);

				//If resource is not found
				if(found==nullptr){
					cout<<"Resource not found\n\n";
					break;
				}

				//If resource is unavailable (WAITLIST ADDING GOES HERE) 
				if(!found->getAvail()){
					cout<<"NEED WAITLIST FUNCTIONALITY\n\n";
					break;
				}

				//Get reservation info
				cout << "Enter student ID: ";
				cin >> studId;
				cin.ignore();                            
				cout << "Enter student name: ";
				getline(cin, name);
				cout << "Enter date (MM/DD/YYYY): ";
				cin >> date;

				//Create it with the next ID and add to list
				Reservation newRes(++nextRevID, studId, id, name, date);
				reservation.insertReservation(newRes);
				cout << "Reservation created.\n";
				break;
			}
			//Remove Reservation (NEED CANCELLATION STUFF HERE)
			case 3:{
				Reservation removed;

				cout<<"Enter reservation ID to cancel :";
				cin>>revId;

				//If it is able to remove it does, cancellation stack goes here
				if(reservation.removeReservation(revId,removed)){
					cout<<"Canceled reservation"<< removed.reservationId<<"\n\n";
				}
				else{
					cout<<"Reservation not found.\n\n";
				}

				break;
			}
			//Display Reservations
			case 4:
				reservation.displayReservations();
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
    return 0;
}
