# Reservation Management System

A C++ reservation management system that demonstrates the use of fundamental data structures including **Linked Lists, Queues, and Stacks**.

The project allows users to create, manage, cancel, and view reservations while maintaining a waiting list and supporting undo functionality.

## Project Overview

The Reservation Management System is designed to simulate a simple reservation system.

The project uses different data structures for different purposes:

* **Linked List** → Stores active reservations
* **Queue (FIFO)** → Manages customers on the waiting list
* **Stack (LIFO)** → Stores cancelled reservations for undo functionality

This project also demonstrates important programming concepts such as:

* Object-Oriented Programming
* Dynamic memory
* Pointers
* Classes and objects
* Linked lists
* Queues
* Stacks
* Searching
* Insertion and deletion
* Big-O time complexity

## Features

### 1. Add Reservation

Users can create a new reservation.

If there is available space, the reservation is added to the active reservation list.

### 2. Remove Reservation

Users can cancel an existing reservation.

The reservation is removed from the active reservation list and can be stored in the undo stack.

### 3. Waiting List

When the reservation capacity is full, new customers can be added to the waiting list.

The waiting list follows the **FIFO (First In, First Out)** principle.

For example:

```text
Customer A
Customer B
Customer C
```

Customer A will be served first.

### 4. Undo Cancellation

The system uses a stack to keep track of cancelled reservations.

The most recently cancelled reservation can be restored first.

This follows the **LIFO (Last In, First Out)** principle.

Example:

```text
Cancel A
Cancel B
Cancel C
```

Undo will restore:

```text
C
B
A
```

### 5. Display Reservations

The system can display all current reservations.

### 6. Search Reservations

Users can search for a reservation using the available reservation information.

## Data Structures

### Linked List

The active reservations are stored using a linked list.

Each reservation is represented by a node.

```text
Head
 |
 v
[Reservation A] -> [Reservation B] -> [Reservation C] -> NULL
```

Advantages:

* Dynamic size
* Easy insertion and deletion
* Does not require contiguous memory

Typical complexity:

| Operation           | Time Complexity |
| ------------------- | --------------: |
| Insert at beginning |            O(1) |
| Search              |            O(n) |
| Remove/Search       |            O(n) |
| Traverse            |            O(n) |

### Queue

The waiting list uses a queue.

A queue follows:

**FIFO — First In, First Out**

```text
Front
  |
  v
[A] -> [B] -> [C]
             |
            Rear
```

Customer A will leave the queue first.

Typical complexity:

| Operation | Time Complexity |
| --------- | --------------: |
| Enqueue   |            O(1) |
| Dequeue   |            O(1) |
| Peek      |            O(1) |

### Stack

The undo system uses a stack.

A stack follows:

**LIFO — Last In, First Out**

```text
Top
 |
 v
[C]
[B]
[A]
```

The most recently cancelled reservation is restored first.

Typical complexity:

| Operation | Time Complexity |
| --------- | --------------: |
| Push      |            O(1) |
| Pop       |            O(1) |
| Top       |            O(1) |

## Project Structure

Reservation-Management-System/
│
├── main.cpp
│

│
└── README.md
``+++++++

### `main.cpp`

Contains the main program and user interaction.

### `Reservation.h`

Defines the `Reservation` class and its data members and functions.

### `Reservation.cpp`

Contains the implementation of the `Reservation` class.

### `ReservationManager.h`

Defines the `ReservationManager` class responsible for managing reservations, waiting lists, and undo operations.

### `ReservationManager.cpp`

Contains the implementation of the reservation management system.

### `Resource.h`

Contains project resources or shared definitions used by the program.

### `README.md`

Contains documentation about the project.

## Example Workflow

A typical workflow could look like this:

```text
1. Create Reservation
        ↓
2. Check Capacity
        ↓
   ┌───────────────┐
   │ Space exists? │
   └───────┬───────┘
       Yes │ No
           │
           ↓
     Add Reservation
           │
           ↓
     Reservation List


If there is no space:

        ↓
   Waiting Queue
        ↓
   Customer waits
```

When a reservation is cancelled:

```text
Active Reservation
        ↓
    Cancel
        ↓
   Remove from
 Reservation List
        ↓
   Push onto Stack
        ↓
    Undo Stack
```

## Example

Suppose the system has three reservations:

```text
Reservation List:

Alice -> Bob -> Charlie -> NULL
```

Alice cancels her reservation:

```text
Reservation List:

Bob -> Charlie -> NULL
```

The cancelled reservation is placed in the undo stack:

```text
Undo Stack:

Alice
```

If the user selects Undo, Bob is restored first because the stack follows LIFO.

## Time Complexity

The project demonstrates how different data structures affect algorithm performance.

| Operation               | Data Structure | Complexity |
| ----------------------- | -------------- | ---------: |
| Add reservation         | Linked List    |      O(1)* |
| Search reservation      | Linked List    |       O(n) |
| Remove reservation      | Linked List    |       O(n) |
| Add waiting customer    | Queue          |       O(1) |
| Remove waiting customer | Queue          |       O(1) |
| Cancel reservation      | Stack          |       O(1) |
| Undo cancellation       | Stack          |       O(1) |

`*` Adding at the head of the linked list is O(1). If the program must search for a specific location before insertion, the overall operation may be O(n).

## Concepts Demonstrated

This project was created to practice:

### C++

* Classes
* Objects
* Constructors
* Member functions
* Pointers
* Dynamic memory allocation
* Header files
* Source files
* Encapsulation

### Data Structures

* Singly linked lists
* Queues
* Stacks

### Algorithms

* Searching
* Insertion
* Deletion
* Traversal
* Undo operations

### Computer Science Concepts

* FIFO
* LIFO
* Big-O notation
* Memory management
* Algorithm efficiency

## How to Compile

Make sure you have a C++ compiler installed, such as **G++**.

### Compile

From the project directory:

```bash
g++ main.cpp Reservation.cpp ReservationManager.cpp -o reservation
```

### Run

On Windows:

```bash
reservation.exe
```


## Requirements

* C++ compiler
* C++11 or newer
* Git (optional, for version control)
* GitHub account (optional, for publishing the project)

## Future Improvements

Possible improvements include:

* Add a graphical user interface
* Store reservations in a file
* Load reservations when the program starts
* Add user authentication
* Add date and time validation
* Add reservation modification
* Add multiple reservation types
* Improve error handling
* Add automated unit tests
* Use smart pointers for safer memory management

## Learning Goals

The main goal of this project is to understand how data structures can be applied to solve real-world problems.

The project demonstrates that different problems require different data structures:

## Author

**Mahamat Mahamat Moussa**
**Nathan Moody**
** IHEZIE THEO-UKA**


