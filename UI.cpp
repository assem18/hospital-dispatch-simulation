#pragma once
#include <iostream>
#include "UI.h"

// Function to print the list of hospitals
void UI::printHospitalss(LinkedQueue<Hospital*>& hospitalQueue) {
    LinkedQueue<Hospital*> tempQueue = hospitalQueue;
    if (tempQueue.size() == 0) {
        cout << "No hospitals available." << endl;
        return;
    }

    cout << "===== Hospitals List =====" << endl;
    while (tempQueue.size() > 0) {
        Hospital* hospital;
        tempQueue.dequeue(hospital);
        cout << hospital << endl;  // Assumes << operator is overloaded for Hospital*
    }
}