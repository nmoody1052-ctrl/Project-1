#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

// Stores the information for ONE reservation
struct Reservation {
    int reservationId;
    int studentId;
    int resourceId;
    std::string timestamp;

    Reservation(
        int reservationId = 0,
        int studentId = 0,
        int resourceId = 0,
        const std::string& timestamp = ""
    );
};

// One node in the active-reservation linked list
struct ReservationNode {
    Reservation data;
    ReservationNode* next;

    explicit ReservationNode(const Reservation& reservation);
};

#endif
