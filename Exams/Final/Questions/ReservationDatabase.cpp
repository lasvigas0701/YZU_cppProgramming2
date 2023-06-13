#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string phoneNumber )
{





}

void ReservationDatabase::displayReservationInfo( string phoneNumber )
{
   cout << endl;
   int count = 0;
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getPhoneNumber() == phoneNumber )
      {
         cout << setw( 2 ) << ++count << ". ";
         it->displayReservationInfo();
      }
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{
   ifstream inReservationFile( "Reservations.dat", ios::binary );





   inReservationFile.close();
}

void ReservationDatabase::storeReservations()
{
   ofstream outReservationFile( "Reservations.dat", ios::binary );





   outReservationFile.close();
}