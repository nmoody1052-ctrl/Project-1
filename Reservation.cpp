#include "Reservation.h"

Reservation::Reservation(
    int reservationId,
    int studentId,
    int resourceId,
    const std::string& timestamp
)
    : reservationId(reservationId),
      studentId(studentId),
      resourceId(resourceId),
      timestamp(timestamp) {
}

ReservationNode::ReservationNode(
    const Reservation& reservation
)
    : data(reservation),
      next(nullptr) {
}
