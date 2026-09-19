#include "ReservationManager.h"
#include <iostream>

// Constructor
ReservationManager::ReservationManager()
    : head(nullptr),
      nextReservationId(1) {
}

// Destructor
ReservationManager::~ReservationManager() {

    ReservationNode* current = head;

    while (current != nullptr) {

        ReservationNode* next = current->next;

        delete current;

        current = next;
    }

    head = nullptr;
}

// =====================================================
// CREATE / INSERT RESERVATION
// =====================================================

bool ReservationManager::createReservation(
    int studentId,
    int resourceId,
    const std::string& timestamp
) {

    // Create reservation data
    Reservation reservation(
        nextReservationId,
        studentId,
        resourceId,
        timestamp
    );

    // Create a new linked-list node
    ReservationNode* newNode =
        new ReservationNode(reservation);

    // Insert at the HEAD
    newNode->next = head;
    head = newNode;

    // Give the next reservation a new ID
    nextReservationId++;

    return true;
}

// =====================================================
// DELETE / REMOVE RESERVATION
// =====================================================

bool ReservationManager::deleteReservation(
    int reservationId
) {

    ReservationNode* current = head;
    ReservationNode* previous = nullptr;

    // Traverse until reservation is found
    while (
        current != nullptr &&
        current->data.reservationId != reservationId
    ) {
        previous = current;
        current = current->next;
    }

    // Reservation was not found
    if (current == nullptr) {
        return false;
    }

    // If deleting the HEAD node
    if (previous == nullptr) {

        head = current->next;
    }

    // If deleting a middle/end node
    else {

        previous->next = current->next;
    }

    // Free memory
    delete current;

    return true;
}

// =====================================================
// VALIDATE / SEARCH RESERVATION
// =====================================================

bool ReservationManager::validateReservation(
    int reservationId
) const {

    ReservationNode* current = head;

    // Traverse the linked list
    while (current != nullptr) {

        if (current->data.reservationId == reservationId) {
            return true;
        }

        current = current->next;
    }

    return false;
}

// =====================================================
// FIND RESERVATION
// =====================================================

ReservationNode* ReservationManager::findReservation(
    int reservationId
) {

    ReservationNode* current = head;

    while (current != nullptr) {

        if (current->data.reservationId == reservationId) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

// =====================================================
// DISPLAY / TRAVERSE
// =====================================================

void ReservationManager::displayReservations() const {

    ReservationNode* current = head;

    std::cout << "\nActive Reservations:\n";

    std::cout << "HEAD";

    while (current != nullptr) {

        std::cout
            << " -> [Reservation ID: "
            << current->data.reservationId
            << " | Student ID: "
            << current->data.studentId
            << " | Resource ID: "
            << current->data.resourceId
            << " | Date: "
            << current->data.timestamp
            << "]";

        current = current->next;
    }

    std::cout << " -> NULL\n";
}

// =====================================================
// GET HEAD
// =====================================================

ReservationNode* ReservationManager::getHead() const {
    return head;
}
