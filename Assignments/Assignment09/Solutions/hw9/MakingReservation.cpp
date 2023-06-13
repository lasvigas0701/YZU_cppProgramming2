#include "MakingReservation.h"
#include <iostream>
#include <iomanip>
using namespace std;

MakingReservation::MakingReservation(ReservationDatabase& reservation, FlightSchedule& flight)
    : allReservations(reservation), allFlights(flight)
{
}

void MakingReservation::execute()
{
    int departureAirport;
    do {
        cout << "\nDeparture airport:\n";
        for (int i = 1; i <= 11; i++)
            cout << setw(2) << i << ". " << airportName[i] << endl;
        cout << "? ";

        cin >> departureAirport;
    } while (departureAirport < 1 || departureAirport > 11);

    int arrivalAirport;
    chooseArrivalAirport(departureAirport, arrivalAirport);

    Reservation newReservation("", "", "", "", "");
    string date;
    cout << "\nDeparture date (yyyy/mm/dd): ";
    cin >> date;
    cout << endl;
    newReservation.setDate(date);

    /*load all flights from departureAirport to arrivalAirport.*/
    FlightSchedule canChooseFlights(departureAirport, arrivalAirport);

    vector<Flight> flights;
    canChooseFlights.getFlights(flights);

    canChooseFlights.displayFlights(departureAirport, arrivalAirport, date);

    /*Choose the flight from departureAirport to arrivalAirport by inputting flightNo.*/
    chooseFlight(newReservation, flights, flights.size());

    /*input amount of tickets for each type, and modify totalNumTickets 
      to check if the booking can be completed*/
    int totalNumTickets = 0;
    inputNumTickets(newReservation, totalNumTickets);
    
    if (totalNumTickets == 0)
    {
        cout << "Your booking could not be completed!\n";
        return;
    }

    allReservations.displayReservation(newReservation,allFlights);

    /*input the user's infomation*/
    inputDetails(newReservation);

    /*insert newReservation to the end if allReservations(push_back)*/
    allReservations.addReservation(newReservation);

    cout << "\nBooking completed!\n";
}

void MakingReservation::chooseArrivalAirport(int depart, int& arrive)
{
    bool canArrive[13]{}; /*a boolean array to record if there is any flight from depart to arrive*/

    do {
        cout << "\nArriving airport:\n";
        for (int i = 1; i <= 12; i++) { /*airport code*/
            if (fullFare[depart][i] == 0) continue;
                cout << right << setw(2) << i << ". " << airportName[i] << endl;
            canArrive[i] = 1; 
        }

        cout << "? ";
        cin >> arrive;
    } while (!canArrive[arrive]);
}

void MakingReservation::chooseFlight(Reservation& newReservation, vector<Flight> flights, int flightNum)
{
    string fliNo;
    bool haveTheFlight = false;

    do {
        cout << "\nFlight number: ";
        cin >> fliNo;
        for (int i = 0; i < flightNum; i++) {
            if (fliNo == flights[i].getFlightNo()) {
                haveTheFlight = true;
                newReservation.setFlightNo(fliNo);
            }
        }
    } while (!haveTheFlight);

}

void MakingReservation::inputNumTickets(Reservation& newReservation, int& totalNum)
{
    int buffer[8]{};
    do {
        cout << "\nNumber of infant tickets (0 ~ 4): ";
        cin >> buffer[3];
    } while (buffer[3] < 0 || buffer[3] > 4);

    int numTickets = 0;
    int numAdults = 0;
    do
    {
        numTickets = 0;

        cout << "\nNumber of full fare tickets (0 ~ 4): ";
        cin >> buffer[1];
        numTickets += buffer[1];

        cout << "\nNumber of child tickets (0 ~ 4): ";
        cin >> buffer[2];
        numTickets += buffer[2];

        cout << "\nNumber of senior citizen tickets (0 ~ 4): ";
        cin >> buffer[4];
        numTickets += buffer[4];

        cout << "\nNumber of impaired tickets (0 ~ 4): ";
        cin >> buffer[5];
        numTickets += buffer[5];

        cout << "\nNumber of impaired companion tickets (0 ~ 4): ";
        cin >> buffer[6];
        numTickets += buffer[6];

        cout << "\nNumber of military tickets (0 ~ 4): ";
        cin >> buffer[7];
        numTickets += buffer[7];

        numAdults = buffer[1] + buffer[4] + buffer[5] + buffer[6] + buffer[7];

        if (numTickets > 4)
            cout << "\nThis booking system accepts a maximum of 4 passengers"
            << "( including children ) per booking.\n"
            << "If there are more than 4 passengers, please make multiple bookings.\n";
        else if (numAdults < buffer[3])
            cout << "\nEach infant must always be accompanied by at least one adult.\n";

        totalNum = numTickets + buffer[3];

    } while (numTickets > 4 || numAdults < buffer[3]);

    newReservation.setTickets(buffer);

    cout << endl;
}

void MakingReservation::inputDetails(Reservation& newReservation)
{
    string id, name, mobile;
    cout << "\nID number: ";
    cin >> id;
    newReservation.setID(id);

    //// check if there is a record, x, of Reservations.dat such that
    //// x.flightNo == reservation.flightNo, x.id == reservation.id and
    //// x.date == reservation.date
    //if (duplicate(reservation))
    //    return;

    cout << "\nName: ";
    cin >> name;
    newReservation.setName(name);

    cout << "\nMobile: ";
    cin >> mobile;
    newReservation.setMobile(mobile);

}
