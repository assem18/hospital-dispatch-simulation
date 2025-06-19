#include "Patient.h"
#include <iostream>

// -------------------- Patient Base Class --------------------
Patient::Patient()
    : request_time(0), pickup_time(0), PID(0), HID(0), distance(0.0),
      waitingtime(0), Finishtime(0), assignmentTime(0), next(nullptr),
      picked(false), assignedCar(nullptr) {}

Patient::Patient(int request_time, int PID, int HID, double d)
    : request_time(request_time), pickup_time(0), PID(PID), HID(HID), distance(d),
      waitingtime(0), Finishtime(0), assignmentTime(0), next(nullptr),
      picked(false), assignedCar(nullptr) {}

void Patient::set_request_time(int rt) { request_time = rt; }
void Patient::set_pickup_time(int pickt) { pickup_time = pickt; }
void Patient::set_pid(int id) { PID = id; }
void Patient::set_hi(int hi) { HID = hi; }
void Patient::set_distance(double d) { distance = d; }
void Patient::set_patient_type(std::string ptype) { patient_type = ptype; }
void Patient::set_waiting_time(int wt) { waitingtime = wt; }
void Patient::set_Finish_time(int ft) { Finishtime = ft; }
void Patient::set_assignmentTime(int at) { assignmentTime = at; }
void Patient::set_next(Patient* nextPatient) { next = nextPatient; }
void Patient::set_picked(bool p) { picked = p; }
void Patient::setAssignedCar(Car* car) { assignedCar = car; }

int Patient::get_request_time() { return request_time; }
int Patient::get_pickup_time() { return pickup_time; }
int Patient::get_pid() { return PID; }
int Patient::get_hi() { return HID; }
double Patient::get_distance() { return distance; }
std::string Patient::get_patient_type() { return patient_type; }
int Patient::get_waitingtime() { return waitingtime; }
int Patient::get_Finishtime() { return Finishtime; }
int Patient::get_assignmentTime() { return assignmentTime; }
Patient* Patient::get_next() { return next; }
bool Patient::is_picked() { return picked; }
Car* Patient::getAssignedCar() const { return assignedCar; }
void Patient::setCurrentTime(int time) {
    currnettime = time;
}

// Getter for current_time
int Patient::getCurrentTime() const {
    return currnettime;
}

Patient::~Patient() {}

NP::NP(int request_time, int PID, int HID, double d) 
    : Patient(request_time, PID, HID, d) {}

void NP::set_cancellationTime(int ct) { cancellationTime = ct; }
int NP::get_cancellationTime() { return cancellationTime; }

// Override the pure virtual function
void NP::print() const {
    std::cout << "NP Patient - ID: " << PID 
              << ", Request Time: " << request_time 
              << ", HID: " << HID 
              << ", Distance: " << distance << std::endl;
}


SP::SP(int request_time, int PID, int HID, double d) 
    : Patient(request_time, PID, HID, d) {}

// Override the pure virtual function
void SP::print() const {
    std::cout << "SP Patient - ID: " << PID 
              << ", Request Time: " << request_time 
              << ", HID: " << HID 
              << ", Distance: " << distance << std::endl;
}

EP::EP(int request_time, int PID, int HID, double d, int cs) 
    : Patient(request_time, PID, HID, d), case_severity(cs) {}

void EP::setSeverity(int cs) { case_severity = cs; }
int EP::getSeverity() { return case_severity; }

// Override the pure virtual function
void EP::print() const {
    std::cout << "EP Patient - ID: " << PID 
              << ", Request Time: " << request_time 
              << ", HID: " << HID 
              << ", Distance: " << distance 
              << ", Severity: " << case_severity << std::endl;
}

