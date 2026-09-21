#include "reservation.h"

Reservation::Reservation(int resId, int sId, std::string sName,
                          std::string rId, std::string time)
    : reservationId(resId), studentId(sId), studentName(sName),
      resourceId(rId), timestamp(time) {}

ReservationNode::ReservationNode(const Reservation& res)
    : data(res), next(nullptr) {}
