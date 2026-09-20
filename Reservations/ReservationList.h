#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H
#include "ReservationList.h"
#include "reservation.h"
    class ReservationList{
        private:
            ReservationNode* head;
        public:
        //Constructor
            ReservationList();
        //End

        //Disable copying
            ReservationList(const ReservationList&) = delete;
        ReservationList& operator=(const ReservationList&) = delete;
        //End

        //Destructor
            ~ReservationList();
        //End
        
        //Insert at front
            void insertReservation(const Reservation& r);
        //End

        //Remove
            // Remove by ID. Returns true if found; the removed data is copied into
            // 'removed' so it can go on the cancellation stack.
            bool removeReservation(int resID, Reservation& removed);
        //End

        //Find
            // Returns the matching node, or nullptr if not found
            ReservationNode* findReservation(int resID);
        //End

        //Display
            void displayReservations() const;
        //End
    };

#endif