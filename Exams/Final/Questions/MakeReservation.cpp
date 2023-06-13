#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h"

extern int inputAnInteger( int begin, int end );

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
   AvailSeatsDatabase &theSeatsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availSeatsDatabase( theSeatsDatabase )
{
}

void MakeReservation::execute()
{
   cout << "\nEnter the party size (1~6): ";

   int partySize;
   do cout << "? ";
   while( ( partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   cout << "\nCurrent date: ";
   cout << currentDate.getYear() << "/" << currentDate.getMonth() << "/" << currentDate.getDay() << endl;

   Date date;
   inputDate( date, currentDate, partySize );

   int timeCode;
   inputTimeCode( timeCode, date, partySize );

   string name;
   cout << "\nEnter name: ";
   cin >> name;

   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   Reservation newReservation( phoneNumber, name, date, timeCode, partySize );

   cout << endl;
   newReservation.displayReservationInfo();

   cout << "\nReservation Completed.\n";

   reservationDatabase.pushBack( newReservation );

   availSeatsDatabase.decreaseAvailSeats( date, timeCode, partySize );
}

void MakeReservation::inputDate( Date &date, Date currentDate, int partySize )
{





}

void MakeReservation::inputTimeCode( int &timeCode, Date date, int partySize )
{





}