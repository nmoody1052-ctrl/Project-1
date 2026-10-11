#include "ReservationManager.h"
#include <iostream>

ReservationManager::ReservationManager()
    : nextReservationId(1), head(nullptr) {}

ReservationManager::~ReservationManager() {
    while (head != nullptr) {
        ReservationNode* next = head->next;
        delete head;
        head = next;
    }
}

void ReservationManager::insertActiveReservation(const Reservation& reservation) {
    ReservationNode* newNode = new ReservationNode(reservation);
    newNode->next = head;
    head = newNode;
}

bool ReservationManager::createReservation(const std::string& resourceId, int studentId,
                                            const std::string& studentName,
                                            const std::string& timestamp,
                                            bool resourceAvailable) {
    if (resourceId.empty() || studentId <= 0 || timestamp.empty()) {
        std::cout << "Invalid reservation. Resource ID, student ID, and date are required.\n";
        return false;
    }

    if (!resourceAvailable) {
        waitlist.push({resourceId, studentId, studentName, timestamp});
        std::cout << "Resource unavailable. Student " << studentId
                  << " added to the waiting list.\n";
        return false;
    }

    Reservation reservation(nextReservationId++, studentId, studentName, resourceId, timestamp);
    insertActiveReservation(reservation);
    std::cout << "Reservation #" << reservation.reservationId << " created.\n";
    return true;
}

void ReservationManager::loadExistingReservation(const Reservation& reservation) {
    insertActiveReservation(reservation);
    if (reservation.reservationId >= nextReservationId) {
        nextReservationId = reservation.reservationId + 1;
    }
}

// --- REMOVAL (Delete Node by ID) ---
// Traverses linked list to find reservationId, updates pointers, and frees memory
bool ReservationManager::cancelReservation(int reservationId) {
    ReservationNode* curr = head;
    ReservationNode* prev = nullptr;

    // Search/Traversal phase
    while (curr != nullptr && curr->data.reservationId != reservationId) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        std::cout << "Error: Reservation #" << reservationId << " not found.\n";
        return false;
    }

    // Removal phase (relinking pointers around 'curr')
    if (prev == nullptr) {
        head = curr->next; // Removing head node
    } else {
        prev->next = curr->next; // Bypass current node
    }

    undoStack.push(curr->data);
    delete curr;
    std::cout << "Reservation #" << reservationId << " cancelled.\n";
    return true;
}

bool ReservationManager::restoreLastCancelled() {
    if (undoStack.empty()) {
        std::cout << "No cancelled reservation is available to restore.\n";
        return false;
    }

    Reservation reservation = undoStack.top();
    undoStack.pop();
    insertActiveReservation(reservation);
    std::cout << "Reservation #" << reservation.reservationId << " restored.\n";
    return true;
}

ReservationNode* ReservationManager::searchReservation(int reservationId) const {
    ReservationNode* curr = head;
    while (curr != nullptr) {
        if (curr->data.reservationId == reservationId) {
            return curr; // Found target node
        }
        curr = curr->next;
    }
    return nullptr; // Not found
}

void ReservationManager::displayActiveReservations() const {
    const ReservationNode* curr = head;
    std::cout << "\nActive reservations\n";
    if (curr == nullptr) {
        std::cout << "None\n";
        return;
    }
    while (curr != nullptr) {
        std::cout << "Reservation #" << curr->data.reservationId
                  << " | Student: " << curr->data.studentId
                  << " (" << curr->data.studentName << ")"
                  << " | Resource: " << curr->data.resourceId
                  << " | Date: " << curr->data.timestamp << "\n";
        curr = curr->next;
    }
}

void ReservationManager::displayWaitingList() const {
    std::queue<WaitingRequest> requests = waitlist;
    std::cout << "\nWaiting list (front to back)\n";
    if (requests.empty()) {
        std::cout << "None\n";
        return;
    }
    while (!requests.empty()) {
        WaitingRequest request = requests.front();
        requests.pop();
        std::cout << "Student: " << request.studentId
                  << " (" << request.studentName << ")"
                  << " | Resource: " << request.resourceId
                  << " | Date: " << request.timestamp << "\n";
    }
}

void ReservationManager::displayCancellationHistory() const {
    std::stack<Reservation> history = undoStack;
    std::cout << "\nCancellation history (most recent first)\n";
    if (history.empty()) {
        std::cout << "None\n";
        return;
    }
    while (!history.empty()) {
        Reservation reservation = history.top();
        history.pop();
        std::cout << "Reservation #" << reservation.reservationId
                  << " | Student: " << reservation.studentId
                  << " (" << reservation.studentName << ")"
                  << " | Resource: " << reservation.resourceId
                  << " | Date: " << reservation.timestamp << "\n";
    }
}

bool ReservationManager::processNextWaitingRequest(const std::string& resourceId, bool resourceAvailable) {
    if (!resourceAvailable) {
        std::cout << "That resource is still unavailable.\n";
        return false;
    }

    std::queue<WaitingRequest> remaining;
    WaitingRequest selected{};
    bool found = false;
    while (!waitlist.empty()) {
        WaitingRequest request = waitlist.front();
        waitlist.pop();
        if (!found && request.resourceId == resourceId) {
            selected = request;
            found = true;
        } else {
            remaining.push(request);
        }
    }
    waitlist = remaining;

    if (!found) {
        std::cout << "No waiting request was found for that resource.\n";
        return false;
    }

    Reservation reservation(nextReservationId++, selected.studentId, selected.studentName,
                            selected.resourceId, selected.timestamp);
    insertActiveReservation(reservation);
    std::cout << "Waiting request promoted to reservation #"
              << reservation.reservationId << ".\n";
    return true;
}
