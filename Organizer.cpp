#include "Organizer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Hospital.h"
#include "UI.h"

using namespace std;

void Organizer::add_patient(Patient* newpatient) {
    All_patient_list->enqueue(newpatient);
}

void Organizer::add_cancelled(NP* newpatient) {
    Cancellation_list->enqueue(newpatient);
}


void Organizer::addFinishedPatients(Patient* patient)
{
        if (patient->getCurrentTime() >= patient->get_Finishtime()) {
            Finished_list->enqueue(patient);
            cout << "Patient with ID " << patient->get_pid() << " has been added to the finished list." << endl;
        }
     else {
        cout << "Invalid hospital or patient provided!" << endl;
    }
}


void Organizer::setbackcars(Car* cars,int priority) {
    if (!Backcars_list) {
        std::cout << "Error: Backcars_list is not initialized.\n";
        return;
    }
    Backcars_list->enqueue(cars,priority);
}

priQueue<Car*>* Organizer::getbackcars() {
    return Backcars_list;
}

void Organizer::add_out_car(Car* car, int pri) {
    Outcars_list->enqueue(car, pri);
}

void Organizer::add_back_car(Car* car) {
    int priority=0;
    Backcars_list->enqueue(car,priority);
}

void Organizer::set_numhostp(int hospnum) {
    numofhospitals = hospnum;
}

int Organizer::get_numhostp() {
    return numofhospitals;
}

Hospital* Organizer::gethlist() {
    return Hlist;
}

OutcarsQueue<Car*>* Organizer::getoutcars() {
    return Outcars_list;
}

void Organizer::settime(int cur) {
    currenttime = cur;
}

int Organizer::gettime() {
    return currenttime;
}


void Organizer::CarFromFreeToOut(Car* car) {
    Patient* patient = nullptr;
    All_patient_list->peek(patient);
        if ( patient->get_request_time() <= patient->getCurrentTime())
        {
            All_patient_list->dequeue(patient);
            if (patient->get_patient_type()=="EP"){
                EP* ep;
                int hid= patient->get_hi();

                Hlist[ep->get_hi()-1].addEmergencyPatient(ep); 
                car->setAssignedPatient(ep);
                car->setAssignedTime(currenttime);
                car->markAssigned();
                ep->setAssignedCar(car);
                Outcars_list->enqueue(car,ep->getSeverity());
                }
              
              else if(patient->get_patient_type()=="NC")
        {
                NP* np;
                Hlist[np->get_hi() - 1].addNormalPatient(np);
                int pri=0;


                Hlist[np->get_hi()-1].addNormalPatient(np); 
                car->setAssignedPatient(np);
                car->setAssignedTime(currenttime);
                car->markAssigned();
                np->setAssignedCar(car);
                Outcars_list->enqueue(car,pri);
        }
        else
        {
            SP* sp ;
            Hlist[sp->get_hi() - 1].addSpecialPatient(sp);
                int pri=0;
                Hlist[sp->get_hi()-1].addSpecialPatient(sp); 
                car->setAssignedPatient(sp);
                car->setAssignedTime(currenttime);
                car->markAssigned();
                sp->setAssignedCar(car);
                Outcars_list->enqueue(car,pri);
        }
        }
    }








void Organizer::CarFromBackToFree() {

    while (true) {
        Car* car ;
        int priority = 0;
        Backcars_list->peek(car,priority);
      if(car->getcurrenttime()>= car->getFinishTime()){

            Backcars_list->dequeue(car, priority);
            if (car->getCarType() == 0) {
                Hlist[car->getHospitalID()-1].enqueueNormalCar(car);
            }
            else if (car->getCarType() == 1) {
                Hlist[car->getHospitalID()-1].enqueueSpecialCar(car);
            }
            Finished_list->enqueue(car->getAssignedpatient());
            car->removePatient();

        }
        else { break; }
    }
}
    

void Organizer::CarFromOutToBack(Car* car;) {
    
    int pri;
    while(true) {
        Car* c = nullptr;
        int priority = 0;
        Outcars_list->peek(c, priority);
        if (c && priority == curtime)
        {
            Outcars_list->dequeue(c, priority);
            Backcars_list->enqueue(c,priority);

        }
        else { break; }
    }
}

void Organizer::loadfile() {
    ifstream inputfile("input.txt");
    if (!inputfile.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    inputfile >> numofhospitals;
    Hlist = new Hospital[numofhospitals];
    inputfile >> Scarspeed >> Ncarspeed;

    hospitaldist = new int*[numofhospitals];
    for (int i = 0; i < numofhospitals; i++) {
        hospitaldist[i] = new int[numofhospitals];
        for (int j = 0; j < numofhospitals; j++) {
            inputfile >> hospitaldist[i][j];
        }
    }

    int Scars, Ncars;
    for (int i = 0; i < numofhospitals; i++) {
        inputfile >> Scars >> Ncars;
        for (int j = 0; j < Scars; j++) {
            Car* Sc = new Car(Scarspeed, 1, j, Hlist[i].getHID());
            Hlist[i].setSCarSpeed(Scarspeed);
            Hlist[i].enqueueSpecialCar(Sc);
        }
        for (int j = 0; j < Ncars; j++) {
            Car* Nc = new Car(Ncarspeed, 0, j, Hlist[i].getHID());
            Hlist[i].setNCarSpeed(Ncarspeed);
            Hlist[i].enqueueNormalCar(Nc);
        }
    }

    inputfile >> NumReq;
    for (int i = 0; i < NumReq; i++) {
        string requestType;
        int requestTime, patientID, hospitalID, travelDistance, severity;

        inputfile >> requestType;
        if (requestType == "NP") {
            inputfile >> requestTime >> patientID >> hospitalID >> travelDistance;
            NP* np = new NP(requestTime, patientID, hospitalID, travelDistance);
            All_patient_list->enqueue(np);
            Hlist[hospitalID - 1].addNormalPatient(np);
        } else if (requestType == "SP") {
            inputfile >> requestTime >> patientID >> hospitalID >> travelDistance;
            SP* sp = new SP(requestTime, patientID, hospitalID, travelDistance);
            All_patient_list->enqueue(sp);
            Hlist[hospitalID - 1].addSpecialPatient(sp);
        } else if (requestType == "EP") {
            inputfile >> requestTime >> patientID >> hospitalID >> travelDistance >> severity;
            EP* ep = new EP(requestTime, patientID, hospitalID, travelDistance, severity);
            All_patient_list->enqueue(ep);
            Hlist[hospitalID - 1].addEmergencyPatient(ep);
        }
    }

    inputfile >> NumCancReq;
    for (int i = 0; i < NumCancReq; i++) {
        int PID, HID, CT;
        inputfile >> PID >> HID >> CT;
        NP* np = new NP(0, PID, HID, 0);
        Cancellation_list->enqueue(np);
    }

    inputfile.close();

}
bool Organizer::isEmpty() {
    for (int i = 0; i < numofhospitals; i++) {
        if (!Hlist[i].isEmpty()) {
            return false;
        }
    }
    return true;
}




// void Organizer::iterate()
// {
//     Patient* p = nullptr;

//     all_patient_list->peek(p);
//     if (p && p->getRequestTime() <= curtime)
//     {
//         all_patient_list->dequeue(p);
//         // add patients to hospital lists
//         if (dynamic_cast<EP*>(p))
//         {
//             EP* ep = dynamic_cast<EP*>(p);
//             hospitals[ep->getHID() - 1].addEP(ep);
//         }
//         else if (dynamic_cast<NP*>(p))
//         {
//             NP* np = dynamic_cast<NP*>(p);
//             hospitals[np->getHID() - 1].addNP(np);
//         }
//         else
//         {
//             SP* sp = dynamic_cast<SP*>(p);
//             Hospital[sp->getHID() - 1].addSP(sp);
//         }
//     }



void Organizer::Simulate(UI& u) {
    srand(time(0));
    loadfile();
    int count =0;

    while (!isEmpty()) {

        for (int i = 0; i < numofhospitals; i++) {
            Hospital& currenthospital = Hlist[i];
            int randnum = rand() % 100 + 1;

            if (randnum >= 10 && randnum < 20) {
                SP* sp_patient = nullptr;
                if (currenthospital.getSPlist()->dequeue(sp_patient)) {
                    add_finished(sp_patient);
                    std::cout << "Processed SP Patient: ID=" << sp_patient->get_pid() << "\n";
                }
            } else if (randnum >= 20 && randnum < 25) {
                int caseseverity;
                EP* ep_patient = nullptr;
                if (currenthospital.getEPlist()->dequeue(ep_patient, caseseverity)) {
                    add_finished(ep_patient);
                    std::cout << "Processed EP Patient: ID=" << ep_patient->get_pid() << " Severity=" << caseseverity << "\n";
                }
            } else if (randnum >= 30 && randnum < 40) {
                NP* np_patient = nullptr;
                if (currenthospital.getNPlist()->dequeue(np_patient)) {
                    add_finished(np_patient);
                    std::cout << "Processed NP Patient: ID=" << np_patient->get_pid() << "\n";
                }
            } else if (randnum >= 40 && randnum < 45) {
                Car* scar = nullptr;
                if (currenthospital.getSC()->dequeue(scar)) {
                    Outcars_list->enqueue(scar, 1);
                    std::cout << "Special car dispatched from hospital ID=" << currenthospital.getHID() << "\n";
                }
            } else if (randnum >= 70 && randnum < 75) {
                Car* ncar = nullptr;
                if (currenthospital.getNC()->dequeue(ncar)) {
                    Outcars_list->enqueue(ncar, 1);
                    std::cout << "Normal car dispatched from hospital ID=" << currenthospital.getHID() << "\n";
                }
            } else if (randnum >= 80 && randnum < 90) {
                Car* car;
                CarFromOutToBack(car);
            } else if (randnum >= 91 && randnum < 95) {
                Car* car;
                CarFromBackToFree(car);

            }}