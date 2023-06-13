// FlightSchedule.cpp
// Member-function definitions for class FlightSchedule.
#include <iostream>
#include <fstream>
#include "FlightSchedule.h" // FlightSchedule class definition

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



}

void FlightSchedule::loadFlightSchedule()
{



}