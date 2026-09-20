#include "reservation.h"

Reservation::Reservation(int resId, int sId, std::string rId, std::string name, std::string time)
    : reservationId(resId), studentId(sId), resourceId(rId), studentName(name), timestamp(time) {}

ReservationNode::ReservationNode(const Reservation& res)
    : data(res), next(nullptr) {} 


