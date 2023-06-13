#include "FlightSchedule.h"

FlightSchedule::FlightSchedule()
{
	loadFlightSchedule();
}

FlightSchedule::FlightSchedule(int de, int arr)
{
    loadFlightSchedule(de, arr);
}

FlightSchedule::~FlightSchedule()
{
}

void FlightSchedule::displayFlights(int depart, int arrive, string date)
{
    cout << airportName[depart] << " to " << airportName[arrive]
        << " / Depart date: " << date << ".\n\n";
    cout << "Flight   Departure   Arrival   Fare\n";

    for (int i = 0; i < flights.size(); i++)
        /*if (flights[i].getDepartureAirport() == depart && flights[i].getArrivalAirport() == arrive)*/
            cout << setw(6) << flights[i].getFlightNo()
            << setw(12) << flights[i].getDepartureTime()
            << setw(10) << flights[i].getArrivalTime()
            << setw(7) << fullFare[depart][arrive] << endl;
}

void FlightSchedule::getFlights(vector<Flight>& canArriveFlights)
{
    for (size_t i = 0; i < flights.size(); i++)
        canArriveFlights.push_back(flights[i]);
    
}

void FlightSchedule::loadFlightSchedule()
{
    fstream inOutFlight("Flight Schedule.dat", ios::in | ios::out | ios::binary);
    inOutFlight.seekp(0, ios::end);
    int numFlights = static_cast<int>(inOutFlight.tellp()) / 32;
    inOutFlight.seekp(0, ios::beg);
    Flight temp("", 0, 0, "", "");
    for (int i = 0; i < numFlights; i++) {
        inOutFlight.read(reinterpret_cast<char*>(&temp), 32);
        flights.push_back(temp);
    }
        
    inOutFlight.clear();
    inOutFlight.close();
}

void FlightSchedule::loadFlightSchedule(int de, int arr)
{
    fstream inOutFlight("Flight Schedule.dat", ios::in | ios::out | ios::binary);
    inOutFlight.seekp(0, ios::end);
    int numFlights = static_cast<int>(inOutFlight.tellp()) / sizeof(Flight);
    inOutFlight.seekp(0, ios::beg);

    Flight temp("", 0, 0, "", "");
    for (int i = 1; i <= numFlights; i++) {
        inOutFlight.read(reinterpret_cast<char*>(&temp), sizeof(Flight));
        if (temp.getArrivalAirport() == arr && temp.getDepartureAirport() == de)
            flights.push_back(temp);
    }

    inOutFlight.clear();
    inOutFlight.close();
}

vector<Flight>::iterator FlightSchedule::searchFlight(string flightNo)
{
    for (vector<Flight>::iterator it = flights.begin(); it != flights.end(); it++)
        if (it->getFlightNo() == flightNo)
            return it;
    return flights.end();
}
