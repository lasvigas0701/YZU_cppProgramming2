// FlightSchedule.cpp
// Member-function definitions for class FlightSchedule.
#include <iostream>
#include <fstream>
#include "FlightSchedule.h" // FlightSchedule class definition
using namespace std;

// FlightSchedule default constructor loads flight schedule from the file Flight Schedule.dat
FlightSchedule::FlightSchedule()
{
    loadFlightSchedule();
}

FlightSchedule::~FlightSchedule()
{
}

int FlightSchedule::getDepartureAirport( string flightNo )
{
    vector< Flight >::iterator it = getFlight( flightNo );

    if( it != flights.end() )
        return it->getDepartureAirport();

    return 0;
}

int FlightSchedule::getArrivalAirport( string flightNo )
{
    vector< Flight >::iterator it = getFlight( flightNo );

    if( it != flights.end() )
        return it->getArrivalAirport();

    return 0;
}

string FlightSchedule::getDepartureTime( string flightNo )
{
    vector< Flight >::iterator it = getFlight( flightNo );

    return it->getDepartureTime();
}

string FlightSchedule::getArrivalTime( string flightNo )
{
    vector< Flight >::iterator it = getFlight( flightNo );

    return it->getArrivalTime();
}

bool FlightSchedule::exist( string flightNo, int departureAirport, int arrivalAirport )
{
    for (int i = 0; i < flights.size(); i++)
    {
        if (flights[i].getFlightNo() == flightNo && flights[i].getDepartureAirport() == departureAirport
            && flights[i].getArrivalAirport() == arrivalAirport)
            return true;
    }
    return false;
}

void FlightSchedule::display( int departureAirport, int arrivalAirport, string date )
{
    cout << airportName[ departureAirport ] << " to " << airportName[ arrivalAirport ]
        << " / Depart date: " << date << ".\n\n";
    cout << "Flight   Departure   Arrival   Fare\n";

    for( vector< Flight >::iterator it = flights.begin(); it != flights.end(); ++it )
        if( it->getDepartureAirport() == departureAirport &&
            it->getArrivalAirport() == arrivalAirport )
            it->display( date );
}

vector< Flight >::iterator FlightSchedule::getFlight( string flightNo )
{
    vector< Flight >::iterator it = flights.begin();
    for (; it != flights.end(); it++)
        if (it->getFlightNo() == flightNo)
            break;

    return it;
}

void FlightSchedule::loadFlightSchedule()
{
    Flight buf("", 0, 0, "", "");
    fstream inOutFlight("Flight Schedule.dat", ios::in | ios::out | ios::binary);

    if (!inOutFlight)
    {
        cerr << "Flight Schedule.dat could not be opened!\n";
        exit(1);
    }

    /*inOutFlight.seekg(0, ios::end);
    int numFlights = static_cast<int>(inOutFlight.tellg()) / sizeof(Flight);
    inOutFlight.seekg(0, ios::beg);
    for (int i = 0; i < numFlights; i++)
    {
        inOutFlight.read(reinterpret_cast<char*>(&buf), sizeof(Flight));
        flights.push_back(buf);
    }*/

    while (inOutFlight.read(reinterpret_cast<char*>(&buf), sizeof(Flight)))
        flights.push_back(buf);

    inOutFlight.clear();
    inOutFlight.close();
}