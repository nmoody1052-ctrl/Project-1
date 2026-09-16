#include "ReservationManager.h"
#include <iostream>

// --- INSERTION (Head Insertion) ---
// Inserts new reservation at the front of the linked list
bool ReservationManager::createReservation(int studentId, std::string timestamp) {
    if (!managedResource.isAvailable()) {
        std::cout << "Resource unavailable. Student " << studentId << " added to waitlist.\n";
        waitlist.enqueue(studentId);
        return false;
    }

    // Create new node and attach it to the head
    Reservation newRes(nextReservationId++, studentId, managedResource.resourceId, timestamp);
    ReservationNode* newNode = new ReservationNode(newRes);

    newNode->next = head;
    head = newNode;
    
    managedResource.currentBookings++;
    return true;
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

    // Push canceled data to dynamic stack for undo tracking
    undoStack.push(curr->data);
    delete curr;
    managedResource.currentBookings--;

    return true;
}

// --- SEARCHING (Linear Search) ---
// Traverses list sequentially starting from head pointer
ReservationNode* ReservationManager::searchReservation(int reservationId) {
    ReservationNode* curr = head;
    while (curr != nullptr) {
        if (curr->data.reservationId == reservationId) {
            return curr; // Found target node
        }
        curr = curr->next;
    }
    return nullptr; // Not found
}

// --- TRAVERSAL (Display Active Reservations) ---
void ReservationManager::displayActiveReservations() const {
    ReservationNode* curr = head;
    std::cout << "HEAD -> ";
    while (curr != nullptr) {
        std::cout << "[ID: " << curr->data.reservationId 
                  << " | Student: " << curr->data.studentId << "] -> ";
        curr = curr->next;
    }
    std::cout << "NULL\n";
}



