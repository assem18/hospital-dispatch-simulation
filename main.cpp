#include "Organizer.h"
#include "UI.h"
#include <iostream>

int main() {
    // Initialize Organizer and UI objects
    Organizer organizer;
    UI ui;

    // Simulate the system
    try {
        organizer.Simulate(ui);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred during simulation: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Simulation completed successfully." << std::endl;
    return 0;
}
