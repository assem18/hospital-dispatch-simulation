#include "Hospital.h"
using namespace std;


// Constructor
Hospital::Hospital()
    : no_hospitals(0), H_Ids(0), SCarsspeed(0), NCarspedd(0), dist_matrix(nullptr) {}

// Setter and Getter for Car Speeds
void Hospital::setNCarSpeed(int speed) {
    NCarspedd = speed;
}

int Hospital::getNCarSpeed() const {
    return NCarspedd;
}

void Hospital::setSCarSpeed(int speed) {
    SCarsspeed = speed;
}

int Hospital::getSCarSpeed() const {
    return SCarsspeed;
}

// Getters for Lists
LinkedQueue<Car*>* Hospital::getNC() {
    return &NCars_list;
}

LinkedQueue<Car*>* Hospital::getSC() {
    return &SCars_list;
}

ExtLinkedQueue<NP*>* Hospital::getNPlist() {
    return &NP_list;
}

priQueue<EP*>* Hospital::getEPlist() {
    return &EP_list;
}

LinkedQueue<SP*>* Hospital::getSPlist() {
    return &SP_list;
}

// Enqueue Cars
void Hospital::enqueueNormalCar(Car* car) {
    NCars_list.enqueue(car);
}

void Hospital::enqueueSpecialCar(Car* car) {
    SCars_list.enqueue(car);
}

// Setter and Getter for Hospital ID
void Hospital::setHID(int id) {
    H_Ids = id;
}

int Hospital::getHID() const {
    return H_Ids;
}

// Utility Methods



void Hospital::addNormalPatient(NP* patient) {
    if (patient) NP_list.enqueue(patient);
}

void Hospital::addSpecialPatient(SP* patient) {
    if (patient) SP_list.enqueue(patient);
}

void Hospital::addEmergencyPatient(EP* patient) {
    if (patient) EP_list.enqueue(patient, patient->getSeverity());
}

bool Hospital::isEmpty() {
    return NP_list.isEmpty() && EP_list.isEmpty() && SP_list.isEmpty();
}

void Hospital::checkCars() {
    if (!NCars_list.isEmpty()) {
        Car* normalCar = nullptr;
        NCars_list.dequeue(normalCar);
        if (normalCar) {
            std::cout << "Dequeued from Normal Cars: " << normalCar->getcarid() << "\n";
        }
    } else if (!SCars_list.isEmpty()) {
        Car* specialCar = nullptr;
        SCars_list.dequeue(specialCar);
        if (specialCar) {
            std::cout << "Dequeued from Special Cars: " << specialCar->getcarid() << "\n";
        }
    } else {
        std::cout << "No available cars in both Normal and Special Car lists!\n";
    }
}
void Hospital::assignEP(Patient* patient) {
    if (patient->get_patient_type() != "EP") {
        std::cout << "Error: Patient is not of type EP." << std::endl;
        return;
    }
    if (NCars_list.isEmpty()) {
        std::cout << "Error: No available normal cars to assign." << std::endl;
        return;
    }

    // Check if the patient exists in the EP list
    if (EP_list.isEmpty()) {
        std::cout << "Error: No emergency patients available for assignment." << std::endl;
        return;
    }

    // Dequeue the car and patient
    Car* car = nullptr;
    NCars_list.dequeue(car);
    int priority;

    Patient* assignedPatient = nullptr;
    EP_list.dequeue(assignedPatient,priority);

    // Assign the car to the patient
    car->setAssignedPatient(assignedPatient);
    car->markAssigned();

    std::cout << "Emergency Patient " << assignedPatient->get_pid()
              << " assigned to Car " << car->getcarid() << " successfully." << std::endl;
}

void Hospital::AssignNP(Patient* patient ) {
    Car* car = nullptr;

    if (patient->get_patient_type() == "NP") {
        if (!NCars_list.isEmpty()) {
            NCars_list.dequeue(car); 
            car->setAssignedPatient(patient);
            cout << "NP patient added to NC_list" << endl;
        }

        else {
            cout << "Patient is not of type NP" << endl;
        }
    }}

    void Hospital::assignEP(Patient * patient) {
            Car* car = nullptr;
            
            int priority;
            if (patient->get_patient_type() == "EP") {
                if (!NCars_list.isEmpty()) {
                    NCars_list.dequeue(car);
                    EP_list.dequeue(patient,priority);
                    car->setAssignedPatient(patient);
                    car->markAssigned();
                    cout << "Patient assigned to an NC successfully." << endl;}
        
                else if  (!SCars_list.isEmpty()) {
                    int pri=0;
                    SCars_list.dequeue(car);
                    EP_list.dequeue(patient,pri);
                    car->setAssignedPatient(patient);
                    car->markAssigned();
                    cout << "Patient assigned to an SC successfully." << endl;
                }
            
            
            else {
                cout << "Patient is not of type EP." << endl;
            }
            }}


void Hospital::cancelnp(NP* np){
        NP_list.cancel(np->get_pid());
}

// Destructor
Hospital::~Hospital() {
    // Cleanup SP_list
    while (!SP_list.isEmpty()) {
        SP* patient = nullptr;
        SP_list.dequeue(patient);
        delete patient;
    }

    // Cleanup EP_list
    while (!EP_list.isEmpty()) {
        EP* ep = nullptr;
        int priority = 0;
        EP_list.dequeue(ep, priority);
        delete ep;
    }

    // Cleanup NCars_list
    while (!NCars_list.isEmpty()) {
        Car* car = nullptr;
        NCars_list.dequeue(car);
        delete car;
    }

    // Cleanup SCars_list
    while (!SCars_list.isEmpty()) {
        Car* car = nullptr;
        SCars_list.dequeue(car);
        delete car;
    }

    // Cleanup NP_list
    while (!NP_list.isEmpty()) {
        NP* patient = nullptr;
        NP_list.dequeue(patient);
        delete patient;
    }

    // Cleanup dist_matrix
    if (dist_matrix) {
        for (int i = 0; i < no_hospitals; ++i) {
            delete[] dist_matrix[i];
        }
        delete[] dist_matrix;
    }
}
