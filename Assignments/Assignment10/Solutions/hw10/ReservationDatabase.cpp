// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

// ReservationDatabase default constructor loads flight reservations from the file Reservations.dat
ReservationDatabase::ReservationDatabase()
{
    loadReservations();
}

// ReservationDatabase destructor stores flight reservations into the file Reservations.dat
ReservationDatabase::~ReservationDatabase()
{
    storeReservations();
}

void ReservationDatabase::addReservation( Reservation reservation )
{
    reservations.push_back( reservation );
}

void ReservationDatabase::cancelReservation( string id, int n )
{
    int count = 0;
    for (vector<Reservation>::iterator it = reservations.begin(); it != reservations.end(); it++)
    {
        if (it->getId() == id)
        {
            count++;
            if (count == n)
            {
                reservations.erase(it);
                cout << "\nThe seleted booking has been deleted. \n";
                break;
            }
        }
    }
} // end function cancelReservation

bool ReservationDatabase::empty()
{
    return ( reservations.size() == 0 );
}

bool ReservationDatabase::existReservation( string id )
{
    for (int i = 0; i < reservations.size(); i++)
        if (reservations[i].getId() == id)
            return true;

    return false;
}

void ReservationDatabase::display( string id )
{
    char ticketType[ 8 ][ 24 ] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                        "Senior Citizen Fare", "Impaired Fare",
                                        "Impaired Companion Fare", "Military Fare" };
    int numForID = 0;
    FlightSchedule flightSchedule; /*another method?*/
    for (int k = 0; k < reservations.size(); k++)
    {
        if (reservations[k].getId() == id)
        {
            int depart = flightSchedule.getDepartureAirport(reservations[k].getFlightNo()),
                arrive = flightSchedule.getArrivalAirport(reservations[k].getFlightNo());

            numForID++;
            cout << endl << endl << numForID << ". ";
            cout << "Ticket Information:\n\n";
            cout << "Date: " << reservations[k].getDate() << endl;
            cout << "Flight: B7-" << reservations[k].getFlightNo() << endl << endl;

            cout << right << setw(9) << airportName[depart] << " -> "
                << left << setw(9) << airportName[arrive] << endl;
            cout << right << setw(9) << flightSchedule.getDepartureTime(reservations[k].getFlightNo())
                << "    " << left << setw(9) << flightSchedule.getArrivalTime(reservations[k].getFlightNo()) << endl << endl;

            int total = 0;
            for (int i = 1; i < 8; i++)
            {
                if (reservations[k].getTicket(i))
                {
                    int fare = fullFare[depart][arrive] * discount[i] / 100;
                    cout << right << setw(23) << ticketType[i] << "  TWD " << setw(4)
                        << fare << " x " << reservations[k].getTicket(i) << endl;
                    total += fare * reservations[k].getTicket(i);
                }
            }
            
            cout << "\nTotal: " << total << endl;
        }
    }
}

void ReservationDatabase::loadReservations()
{
    Reservation buf;
    ifstream inReservation("Reservations.dat", ios::in | ios::binary);
    if (!inReservation)
    {
        cerr << "Reservations.dat in loadReservations could not be opened\n";
        exit(1);
    }

    /*inReservation.seekg(0, ios::end);
    int numRes = static_cast<int>(inReservation.tellg()) / sizeof(Reservation);
    inReservation.seekg(0, ios::beg);
    for (int i = 0; i < numRes; i++)
    {
        inReservation.read(reinterpret_cast<char*>(&buf), sizeof(Reservation));
        reservations.push_back(buf);
    }*/

    while (inReservation.read(reinterpret_cast<char*>(&buf), sizeof(Reservation)))
        reservations.push_back(buf);

    inReservation.clear();
    inReservation.close();
}

void ReservationDatabase::storeReservations()
{
    ofstream outReservations("Reservations.dat", ios::out | ios::binary);
    if (!outReservations)
    {
        cerr << "Reservations.dat in storeReservations could not be opened!\n";
        exit(1);
    }

    for (int i = 0; i < reservations.size(); i++)
        outReservations.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));

    outReservations.clear();
    outReservations.close();
}