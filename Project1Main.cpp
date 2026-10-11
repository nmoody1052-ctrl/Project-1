//Include
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
//End

//Headers
        //Here for resource managment
#include "resource.h"
#include "resources.h"
        //End
        //Here for reservation managment
#include "ReservationManager.h"
        //End
//End
using namespace std;

//Prints Header
void header(){
        cout<<
        "+-----------------------------------------------+\n"<<
        "|        Computer Science and Engieering        |\n"<<
        "|          CSCE 2110 - Data Structures          |\n"<<
        "|                                               |\n"<<
        "|                    Mahamat                    |\n"<<
        "|              Nathan Moody NJM0184             |\n"<<
        "+-----------------------------------------------+\n\n";
}
//End

//Prints Menu
void menu(){
        cout<<
        "*********************** Menu **********************\n"<<
        "| 1. Display Resources                             |\n"<<
        "| 2. Create a Reservation                          |\n"<<
        "| 3. Cancel a Reservation                          |\n"<<
        "| 4. Display Active Reservations                   |\n"<<
        "| 5. View Waitlist                                 |\n"<<
        "| 6. Process next waiting request for a resource   |\n"<<
        "| 7. Show Cancelation history                      |\n"<<
        "| 8. Undo Cancellation                             |\n"<<
        "| 9. Search Reservations by ID                     |\n"<<
        "| 10. Search Reservations by Name                   |\n"<<
        "| 11. Sort Reservations by Date                    |\n"<<
        "| 12. Search Resources by ID                       |\n"<<
        "| 13. Sort Resources by Popularity                 |\n"<<
        "| 14. Sort Resources by Name                       |\n"<<
        "| 15. Generate Report                              |\n"<<
        "| 0. Exit                                          |\n"<<
        "***************************************************\n"<<
        ">> ";
}
//End

//Reads a menu choice safely, re-prompting on bad input.
int readChoice(){
        int choice;
        while(!(cin >> choice)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
}
//End

//Loads Resource records from a pipe-delimited file: ID|Name|Type|Availability
void loadResources(Resources& res, const string& path){
        ifstream resourceFile(path);
        if (!resourceFile.is_open()) {
                cerr << "Unable to open " << path << "\n";
                return;
        }

        string line;
        while (getline(resourceFile, line)) {
                string id, name, type, availability;
                stringstream row(line);
                if (getline(row, id, '|') && getline(row, name, '|') &&
                    getline(row, type, '|') && getline(row, availability)) {
                        Resource resource;
                        resource.setID(id);
                        resource.setName(name);
                        resource.setType(type);
                        resource.setAvail(availability);
                        res.addResource(resource);
                }
        }
}
//End

//Loads existing Reservation records from a pipe-delimited file:
//ReservationID|StudentID|StudentName|ResourceID|Date
void loadReservations(ReservationManager& manager, const string& path, Resources& res){
        ifstream reservationFile(path);
        if (!reservationFile.is_open()) {
                cerr << "Unable to open " << path << "\n";
                return;
        }

        string line;
        
        while (getline(reservationFile, line)) {
                string reservationIdStr, studentIdStr, studentName, resourceId, timestamp;
                stringstream row(line);
                if (getline(row, reservationIdStr, '|') && getline(row, studentIdStr, '|') &&
                    getline(row, studentName, '|') && getline(row, resourceId, '|') &&
                    getline(row, timestamp)) {
                        try {
                                Resource* resource = res.findResource(resourceId);
                                if(resource == nullptr){
	                                cerr << "Skipping reservation for unknown resource: " << resourceId << "\n";
	                                continue;
                                }
                                int reservationId = stoi(reservationIdStr);
                                int studentId = stoi(studentIdStr);
                                Reservation reservation(reservationId, studentId, studentName,
                                                         resourceId, timestamp);
                                resource->incremCount();
                                manager.loadExistingReservation(reservation);
                        } catch (...) {
                                cerr << "Skipping malformed reservation line: " << line << "\n";
                        }
                }
        }
}
//End

//Report Generation
void reportGen(ReservationManager& manager, Resources res){
        //Start of Report
        cout<<"----------REPORT----------\n\n";
        //End

        //Displays All Active Reservations + How Many
        cout<<"----------ACTIVE-RESERVATIONS----------\n";
        manager.displayActiveReservations();
        cout<<"----------END-OF-RESERVATIONS----------\n\n";
        //End

        //Prints all resources as well as popularity
        cout<<"----------RESOURCES-SORTED-BY-POPULARITY----------\n";
        res.sortByPopularity();
        res.PrintResources();
        cout<<"----------END-OF-RESOURCES----------\n\n";
        //End

        //Prints Waitlist
        cout<<"----------WAITLIST----------\n";
        manager.displayWaitingList();
        cout<<"----------END-OF-WAITLIST----------\n\n";
        //End

        //Prints Cancelations
        cout<<"----------CANCELATIONS----------\n";
        manager.displayCancellationHistory();
        cout<<"----------END-OF-CANCELATIONS----------\n\n";
        //End

        //End of Report
        cout<<"----------END-OF-REPORT----------\n\n";
        //End
        return;
}
//End

int main(){
        //Vars
        Resources res;
        ReservationManager manager(res);
        //End

        //Print Header
        header();
        //End

        //Load starting data
        loadResources(res, "resources.txt");
        cout << "Loaded " << res.getCount() << " resources.\n\n";

        loadReservations(manager, "reservations.txt", res);
        //End

        //Menu loop
        bool running = true;
        while (running) {
                menu();
                int choice = readChoice();

                switch (choice) {
                        //display resources
                        case 1: {
                                res.PrintResources();
                                break;
                        }
                        //create Reservation
                        case 2: {
                                string resourceId, studentIdStr, studentName, timestamp;
                                cout << "Resource ID: ";
                                getline(cin, resourceId);
                                cout << "Student ID: ";
                                getline(cin, studentIdStr);
                                cout << "Student Name: ";
                                getline(cin, studentName);
                                cout << "Date/timestamp: ";
                                getline(cin, timestamp);

                                Resource* resource = res.findResource(resourceId);
                                if (resource == nullptr) {
                                        cout << "No resource found with ID " << resourceId << ".\n";
                                        break;
                                }

                                int studentId = 0;
                                try {
                                        studentId = stoi(studentIdStr);
                                } catch (...) {
                                        cout << "Invalid student ID.\n";
                                        break;
                                }

                                bool created = manager.createReservation(resourceId, studentId, studentName,
                                                                          timestamp, resource->getAvail());
                                if (created) {
                                        resource->setAvail("Unavailable");
                                        resource->incremCount();
                                }
                                else{
                                        resource->incremWaitCount();
                                }
                                break;
                        }
                        //Cancel Reservation
                        case 3: {
                                cout << "Reservation ID to cancel: ";
                                int reservationId = readChoice();
                                manager.cancelReservation(reservationId);
                                break;
                        }
                        //Display Active Reservations
                        case 4:{
                                manager.displayActiveReservations();
                                break;
                        }
                        //View Waiting List
                        case 5: {
                                manager.displayWaitingList();
                                break;
                        }
                        //Proccess Waiting List
                        case 6: {
                                string resourceId;
                                cout << "Resource ID: ";
                                getline(cin, resourceId);
                                Resource* resource = res.findResource(resourceId);
                                if (resource == nullptr) {
                                        cout << "No resource found with ID " << resourceId << ".\n";
                                        break;
                                }
                                bool promoted = manager.processNextWaitingRequest(resourceId, resource->getAvail());
                                if (promoted) {
                                        resource->decremWaitCount();
                                        resource->setAvail("Unavailable");
                                }
                                break;
                        }
                        //View Cancelation History
                        case 7: {
                                manager.displayCancellationHistory();
                                break;
                                
                        }
                        //Restore Last Cancelation
                        case 8: {
                                manager.restoreLastCancelled();
                                break; 
                        }
                        //Search for reservation via ID
                        case 9: {
                                cout << "Reservation ID to search: ";
                                int reservationId = readChoice();
                                ReservationNode* found = manager.searchReservation(reservationId);
                                if (found == nullptr) {
                                        cout << "Reservation #" << reservationId << " not found.\n";
                                } else {
                                        cout << "Reservation #" << found->data.reservationId
                                             << " | Student: " << found->data.studentId
                                             << " (" << found->data.studentName << ")"
                                             << " | Resource: " << found->data.resourceId
                                             << " | Date: " << found->data.timestamp << "\n";
                                }
                                break;
                        }
                        //Search Reservations Via Name
                        case 10: {
                                //Needs Implementation
                                break;
                        }
                        //Sort Reservations via date
                        case 11: {
                                //Needs Implenentation
                                break;
                        }
                        //Search Resources by ID
                        case 12: {
                                string resourceId;
                                cout << "Resource ID: ";
                                getline(cin, resourceId);
                                Resource* found = res.findResource(resourceId);
                                if(found!=nullptr){
                                        cout
                                        <<"Resource exists\n"
                                        <<"ID: "<<found->getID()<<" | "
			                <<"Name: "<<found->getName()<<" | "
			                <<"Type: "<<found->getType()<<" | ";

			                if(found->getAvail()){
				                cout<<"Availability: Available | \n";
			                }
			                else{
				                cout<<"Availability: Unavailable | \n";
			                }

			                cout<<"Number of Reservations: "<<found->getsCount()<<" | "
			                <<"Number of Waitlists: "<<found->getWaitCount()<<" | "
			                <<"Total Popularity (Reservations+Waitlists): "<<found->getWaitCount()+found->getsCount()<<" | "
                                        <<"\n\n";
                                        break;
                                }
                                else{
                                        cout<<"Resource Not Found\n\n";
                                        break;
                                }
                        }
                        //Sort Resources by Popularity
                        case 13: {
                                res.sortByPopularity();
                                break;
                        }
                        //Sort Resources by Name
                        case 14: {
                                res.sortByName();
                                break;
                        }
                        //Generate Report
                        case 15: {
                                reportGen(manager, res);
                                break;
                        }
                        //Exit
                        case 0: {
                                running = false;
                                cout << "Goodbye.\n";
                                break;
                        }
                        default: {
                                cout << "Invalid choice. Pick a number from the menu.\n";
                                break;
                        }
                }
        }
        //End

        return 0;
}
