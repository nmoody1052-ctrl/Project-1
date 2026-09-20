#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

// Represents a single reservation record
struct Reservation {
    int reservationId;
    int studentId;
    int resourceId;
    std::string timestamp;

    Reservation(int resId = 0, int sId = 0, int rId = 0, std::string time = "");
};

// Node structure for the Active Reservations Linked List
struct ReservationNode {
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& res);
};

#endif
