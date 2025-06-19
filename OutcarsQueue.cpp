#pragma once
#include "priQueue.h"
#include "Car.h"
#include <iostream>

template <typename T>
class OutcarsQueue : public priQueue<Car*> {
public:
    // Print function
    void print();

    // Cancel function: Removes a car based on the patient's ID
    Car* cancel(int pid);
};

// Print function implementation
template <typename T>
void OutcarsQueue<T>::print() {
    std::cout << count_q() << " ==> Out cars: ";
    print_noh();
}

// Cancel function implementation
template <typename T>
Car* OutcarsQueue<T>::cancel(int pid) {
    if (this->isEmpty()) {
        return nullptr; // Queue is empty
    }

    priNode<Car*>* prev = nullptr;
    priNode<Car*>* current = this->head; // Assuming 'head' is accessible in priQueue
    int priority;

    // Traverse the queue to find the car with the matching PID
    while (current != nullptr) {
        Car* car = current->getItem(priority); // Get the car
        if (car->getAssignedpatient() != nullptr && car->getAssignedpatient()->get_pid() == pid) {
            // Found the car assigned to the patient with matching PID

            // Update links to remove the node
            if (prev == nullptr) {
                // If removing the head
                this->head = current->getNext();
            } else {
                prev->setNext(current->getNext());
            }

            // Save the car, delete the node, and return the car
            Car* cancelledCar = car;
            delete current;
            return cancelledCar;
        }

        // Move to the next node
        prev = current;
        current = current->getNext();
    }

    return nullptr; // No car found for the given PID
}
