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



} // end function cancelReservation

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::existReservation( string id )
{



}

void ReservationDatabase::display( string id )
{
   char ticketType[ 8 ][ 24 ] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                      "Senior Citizen Fare", "Impaired Fare",
                                      "Impaired Companion Fare", "Military Fare" };



}

void ReservationDatabase::loadReservations()
{



}

void ReservationDatabase::storeReservations()
{



}