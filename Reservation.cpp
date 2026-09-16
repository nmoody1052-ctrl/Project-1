#include "reservation.h"

Reservation::Reservation(int resId, int sId, int rId, std::string time)
    : reservationId(resId), studentId(sId), resourceId(rId), timestamp(time) {}

ReservationNode::ReservationNode(const Reservation& res)
    : data(res), next(nullptr) {}


