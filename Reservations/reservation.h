#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

// Represents a single reservation record
struct Reservation {
    int reservationId;
    int studentId;
    std::string resourceId;
    std::string studentName;
    std::string timestamp;

    Reservation(int resId = 0, int sId = 0, std::string rId = "", std::string name = "",std::string time = "");
};

// Node structure for the Active Reservations Linked List
struct ReservationNode {
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& res);
};

#endif
