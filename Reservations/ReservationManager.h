#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "reservation.h"
#include <queue>
#include <stack>
#include <string>

class ReservationManager {
public:
    ReservationManager();
    ~ReservationManager();

    bool createReservation(const std::string& resourceId, int studentId,
                           const std::string& studentName,
                           const std::string& timestamp, bool resourceAvailable);
    bool cancelReservation(int reservationId);
    bool restoreLastCancelled();
    ReservationNode* searchReservation(int reservationId) const;
    void displayActiveReservations() const;
    void displayWaitingList() const;
    void displayCancellationHistory() const;
    bool processNextWaitingRequest(const std::string& resourceId, bool resourceAvailable);

    // Inserts a reservation that already exists on disk (e.g. loaded from
    // reservations.txt) directly into the active list without touching the
    // waitlist, and keeps nextReservationId ahead of any loaded IDs.
    void loadExistingReservation(const Reservation& reservation);

private:
    struct WaitingRequest {
        std::string resourceId;
        int studentId;
        std::string studentName;
        std::string timestamp;
    };

    int nextReservationId;
    ReservationNode* head;
    std::queue<WaitingRequest> waitlist;
    std::stack<Reservation> undoStack;

    void insertActiveReservation(const Reservation& reservation);
};

#endif
