#include "Car.h"

// Default Constructor
Car::Car() 
    : carid(0), car_type(0), car_speed(0), car_status(Ready), 
      assignedPat(nullptr), pickup_time(0.0), finish_time(0.0), 
      assigned_time(0.0), current_time(0), busytime(0.0), hid(0) {}

// Parameterized Constructor
Car::Car(int cspeed, int ctype, int id, int hospital_id)
    : carid(id), car_type(ctype), car_speed(cspeed), car_status(Ready), 
      assignedPat(nullptr), pickup_time(0.0), finish_time(0.0), 
      assigned_time(0.0), current_time(0), busytime(0.0), hid(hospital_id) {}

// Destructor
Car::~Car() {
    assignedPat = nullptr; // Ensure pointer is nullified
}

// Setters
void Car::setcarid(int cid) { carid = cid; }
void Car::setCarType(int ct) { car_type = ct; }
void Car::setCarSpeed(int cs) { car_speed = cs; }
void Car::setHospitalID(int hospital_id) { hid = hospital_id; }
void Car::setAssignedPatient(Patient* asp) { assignedPat = asp; }
void Car::setPickupTime(double time) { pickup_time = time; }
void Car::setFinishTime(double time) { finish_time = time; }
void Car::setAssignedTime(double time) { assigned_time = time; }
void Car::setcurrenttime(int current_time) { this->current_time = current_time; }
void Car::setBusyTime(double time) { busytime = time; }

void Car::setpatient(Patient* patient) {
    if (car_speed == 0) {
        throw std::invalid_argument("Car speed cannot be zero.");
    }
    if (!patient) {
        throw std::invalid_argument("Patient cannot be null.");
    }
    assignedPat = patient;
    assigned_time = current_time;
    pickup_time = assigned_time + (patient->get_distance() / car_speed);
    finish_time = pickup_time + (patient->get_distance() / car_speed);
}

// Getters
int Car::getCarType() const { return car_type; }
int Car::getCarSpeed() const { return car_speed; }
int Car::getHospitalID() const { return hid; }
int Car::getcurrenttime() const { return current_time; }
double Car::getBusyTime() const { return busytime; }
double Car::getPickupTime() const { return pickup_time; }
double Car::getFinishTime() const { return finish_time; }
double Car::getAssignedTime() const { return assigned_time; }
int Car::getcarid() const { return carid; }
Patient* Car::getAssignedpatient() const { return assignedPat; }

std::string Car::getCarStatus() const { 
    switch (car_status) {
        case Assigned: return "Assigned";
        case Ready: return "Ready";
        case Loaded: return "Loaded";
        default: return "Unknown";
    }
}

// Status Management
void Car::markReady() {
    car_status = Ready;
    std::cout << "Car " << carid << " marked as Ready.\n";
}

void Car::markAssigned() {
    car_status = Assigned;
    std::cout << "Car " << carid << " marked as Assigned.\n";
}

void Car::markLoaded() { 
    car_status = Loaded;
    std::cout << "Car " << carid << " marked as Loaded.\n";
}

// Remove Patient
void Car::removePatient() {
    Car* car;
    assignedPat = nullptr;
    pickup_time = 0;
    finish_time = 0;
    assigned_time = 0;
    std::cout << "Car " << car->getcarid() << " removed its assigned patient.\n";
}
