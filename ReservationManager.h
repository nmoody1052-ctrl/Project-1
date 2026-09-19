#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include <string>

class ReservationManager {
private:
    // Head of ONE linked list containing
    // ALL active reservations
    ReservationNode* head;

    int nextReservationId;

public:
    // Constructor
    ReservationManager();

    // Destructor
    ~ReservationManager();

    // CREATE / INSERT
    bool createReservation(
        int studentId,
        int resourceId,
        const std::string& timestamp
    );

    // DELETE / REMOVE
    bool deleteReservation(int reservationId);

    // SEARCH / VALIDATE
    bool validateReservation(int reservationId) const;

    // Search and return the actual node
    ReservationNode* findReservation(int reservationId);

    // DISPLAY / TRAVERSE
    void displayReservations() const;

    // Get first node
    ReservationNode* getHead() const;
};

#endif
