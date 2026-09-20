#include "reservation.h"
#include "ReservationList.h"
#include <iostream>
using namespace std;
    //Constructor
        ReservationList::ReservationList(){
            head = nullptr;
        }
    //End

    //Destructor
        ReservationList::~ReservationList(){
            ReservationNode* curr = head;
            while(curr != nullptr){
                ReservationNode* nextNode = curr->next;
                delete curr;    
                curr = nextNode;
            }
        }
    //End
        
    //Insert at front
        void ReservationList::insertReservation(const Reservation& r){
            ReservationNode* newNode = new ReservationNode(r);
            newNode->next = head;
            head = newNode;
        }
    //End

    //Remove
        // Remove by ID. Returns true if found; the removed data is copied into
        // 'removed' so it can go on the cancellation stack.
        bool ReservationList::removeReservation(int resID, Reservation& removed){
            ReservationNode* curr = head;
	        ReservationNode* prev = nullptr;

            while(curr != nullptr && curr->data.reservationId != resID){
                prev = curr;
                curr = curr->next;
            }

            if(curr == nullptr){
                //ID not found
                return false;
            }

            removed = curr->data;
            
            if(prev == nullptr){
                head = curr->next;
            }
            else{
                prev->next = curr->next; 
            }

            delete(curr);
            return true;
        }
    //End

    //Find
        // Returns the matching node, or nullptr if not found
        ReservationNode* ReservationList::findReservation(int resID){
            ReservationNode* curr = head;
            while(curr!=nullptr){
                if(curr->data.reservationId == resID){
                    return curr;
                }
                curr = curr->next;
            }
            return nullptr;
        }
    //End

    //Display
        void ReservationList::displayReservations() const{
            if(head == nullptr){
                cout<<"No active reservations.\n";
                return;
            }
            ReservationNode* curr = head;
            while (curr!=nullptr)
            {
                cout<<
                "Reservation ID :"<<curr->data.reservationId<<" | "<<
                "Student ID:"<<curr->data.studentId<<" | "<<
                "Student Name:"<<curr->data.studentName<<" | "<<
                "Resource ID:"<<curr->data.resourceId<<" | "<<
                "Date :"<<curr->data.timestamp<<endl;
                curr = curr->next;
            }
        }
    //End