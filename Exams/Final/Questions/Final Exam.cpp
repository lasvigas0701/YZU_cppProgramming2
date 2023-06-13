#include <iostream>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"

void viewReservation( ReservationDatabase &reservationDatabase );

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]
void computeCurrentDate( Date &currentDate );
bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
   cout << "Welcome to Zuo Zhe Zuo Sushi Wo Shou Si";

   ReservationDatabase reservationDatabase;
   AvailSeatsDatabase availSeatsDatabase;
   MakeReservation makeReservation( reservationDatabase, availSeatsDatabase );

   int choice;
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Make Reservation\n"
         << "2. Reservation Enquiry\n"
         << "3. End Program\n";

      do cout << "? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      switch( choice )
      {
      case 1:
         makeReservation.execute();
         break;
      case 2:
         viewReservation( reservationDatabase );
         break;
      case 3:
         cout << "\nThank you. Goodbye.\n\n";
         system( "pause" );
         return 0;
      default:
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
}

void viewReservation( ReservationDatabase &reservationDatabase )
{
   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   if( reservationDatabase.empty() )
   {
      cout << "\nNo reservations!\n";
      return;
   }

   if( !reservationDatabase.exist( phoneNumber ) )
   {
      cout << "\nYou have no reservations!\n";
      return;
   }

   reservationDatabase.displayReservationInfo( phoneNumber );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void computeCurrentDate( Date &currentDate )
{
   tm structuredTime;
//   time_t rawTime = time( 0 ) - 191 * 24 * 60 * 60; // 2022-12-02
//   time_t rawTime = time( 0 ) - 132 * 24 * 60 * 60; // 2023-01-30
   time_t rawTime = time( 0 );                      // 2023-06-11
//   time_t rawTime = time( 0 ) + 234 * 24 * 60 * 60; // 2024-01-31
   localtime_s( &structuredTime, &rawTime );

   currentDate.year = structuredTime.tm_year + 1900;
   currentDate.month = structuredTime.tm_mon + 1;
   currentDate.day = structuredTime.tm_mday;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}