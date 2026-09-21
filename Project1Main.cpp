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
        "|        CSCE 2110 - Computer Science __        |\n"<<
        "|                                               |\n"<<
        "|                                               |\n"<<
        "|  										  	|\n"<<
        "+-----------------------------------------------+\n\n";
}
//End

//Prints Menu
void menu(){
        cout<<
        "*********************** Menu **********************\n"<<
        "| 1. Display all resources                        |\n"<<
        "| 2. Create a reservation                          |\n"<<
        "| 3. Cancel a reservation                          |\n"<<
        "| 4. Restore last cancelled reservation            |\n"<<
        "| 5. Process next waiting request for a resource   |\n"<<
        "| 6. Display active reservations                  |\n"<<
        "| 7. Display waiting list                          |\n"<<
        "| 8. Display cancellation history                  |\n"<<
        "| 9. Search reservation by ID                      |\n"<<
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

int main(){
        //Vars
        Resources res;
        ReservationManager manager;
        //End

        //Print Header
        header();
        //End

        //Load resources from the pipe-delimited data file.
        ifstream resourceFile("resources.txt");
        if (!resourceFile.is_open()) {
                cerr << "Unable to open resources.txt\n";
                return 1;
        }

        string line;
        while (getline(resourceFile, line)) {
                string id;
                string name;
                string type;
                string availability;
                stringstream row(line);
                if (getline(row, id, '|') && getline(row, name, '|') &&
                    getline(row, type, '|') && getline(row, availability)) {
                        Resource* resource = new Resource();
                        resource->setID(id);
                        resource->setName(name);
                        resource->setType(type);
                        resource->setAvail(availability == "Available");
                        res.addResource(resource);
                }
        }

        cout << "Loaded " << res.getCount() << " resources.\n";

        //Menu loop
        bool running = true;
        while (running) {
                menu();
                int choice = readChoice();

                switch (choice) {
                        case 1: {
                                res.displayAll();
                                break;
                        }
                        case 2: {
                                string resourceId, studentIdStr, timestamp;
                                cout << "Resource ID: ";
                                getline(cin, resourceId);
                                cout << "Student ID: ";
                                getline(cin, studentIdStr);
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

                                // Using the resource's own numeric position in the ID as the reservation's resourceId key.
                                int numericResourceId = 0;
                                try {
                                        numericResourceId = stoi(resourceId);
                                } catch (...) {
                                        numericResourceId = static_cast<int>(res.getCount());
                                }

                                bool created = manager.createReservation(numericResourceId, studentId,
                                                                          timestamp, resource->getAvail());
                                if (created) {
                                        resource->setAvail(false);
                                }
                                break;
                        }
                        case 3: {
                                cout << "Reservation ID to cancel: ";
                                int reservationId = readChoice();
                                manager.cancelReservation(reservationId);
                                break;
                        }
                        case 4: {
                                manager.restoreLastCancelled();
                                break;
                        }
                        case 5: {
                                string resourceId;
                                cout << "Resource ID: ";
                                getline(cin, resourceId);
                                Resource* resource = res.findResource(resourceId);
                                if (resource == nullptr) {
                                        cout << "No resource found with ID " << resourceId << ".\n";
                                        break;
                                }
                                int numericResourceId = 0;
                                try {
                                        numericResourceId = stoi(resourceId);
                                } catch (...) {
                                        numericResourceId = static_cast<int>(res.getCount());
                                }
                                bool promoted = manager.processNextWaitingRequest(numericResourceId,
                                                                                   resource->getAvail());
                                if (promoted) {
                                        resource->setAvail(false);
                                }
                                break;
                        }
                        case 6: {
                                manager.displayActiveReservations();
                                break;
                        }
                        case 7: {
                                manager.displayWaitingList();
                                break;
                        }
                        case 8: {
                                manager.displayCancellationHistory();
                                break;
                        }
                        case 9: {
                                cout << "Reservation ID to search: ";
                                int reservationId = readChoice();
                                ReservationNode* found = manager.searchReservation(reservationId);
                                if (found == nullptr) {
                                        cout << "Reservation #" << reservationId << " not found.\n";
                                } else {
                                        cout << "Reservation #" << found->data.reservationId
                                             << " | Student: " << found->data.studentId
                                             << " | Resource: R" << found->data.resourceId
                                             << " | Date: " << found->data.timestamp << "\n";
                                }
                                break;
                        }
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
