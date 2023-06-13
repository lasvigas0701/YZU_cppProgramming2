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
    for (int i = 0; i < reservations.size(); i++)
    {
        if (phoneNumber == reservations[i].getPhoneNumber())
        {
            return true;
        }
    }

    return false;
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
   if (!inReservationFile)
   {
       cerr << "Reservaions.dat could not be opened!\n";
       exit(1);
   }

   inReservationFile.seekg(0, ios::end);
   size_t numRes = inReservationFile.tellg() / sizeof(Reservation);
   inReservationFile.seekg(0, ios::beg);

   Reservation buf;
   for (int i = 0; i < numRes; i++)
   {
       inReservationFile.read(reinterpret_cast<char*>(&buf), sizeof(Reservation));
       reservations.push_back(buf);
   }

   inReservationFile.close();
}

void ReservationDatabase::storeReservations()
{
   ofstream outReservationFile( "Reservations.dat", ios::binary );

   if (!outReservationFile)
   {
       cerr << "Reservaions.dat could not be opened!\n";
       exit(1);
   }

   for (int i = 0; i < reservations.size(); i++)
   {
       outReservationFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
   }

   outReservationFile.close();
}