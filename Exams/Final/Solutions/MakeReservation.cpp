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
    cout << "\nChoose a date\n";
    int changeLine = 0, input;
    bool canChoose[31] = {};

    for (int i = 1; i < 31; i++)
    {
        Date buf(currentDate + i);
        if (availSeatsDatabase.availableTimes(buf, partySize))
        {
            cout << right << setw(2) << setfill(' ') << i << ". " << buf.getYear() << "/"
                << setw(2) << setfill('0') << buf.getMonth() << "/" 
                << setw(2) << buf.getDay();
            
            cout << "  ";
            changeLine++;
            canChoose[i] = true;
        }
        if (changeLine == 4)
        {
            cout << endl;
            changeLine = 0;
        }
    }
    cout << endl;

    do {
        cout << "? ";
        input = (inputAnInteger(1, 30));
    } while (input == -1 || !canChoose[input]);

    date = currentDate + input;
}

void MakeReservation::inputTimeCode( int &timeCode, Date date, int partySize )
{
    cout << "\nChoose a time\n";
    bool canChoose[5]{};
    string timeDetail;
    for (int i = 1; i < 5; i++)
    {
        switch (i)
        {
        case 1:
            timeDetail = "11:30";
            break;
        case 2:
            timeDetail = "13:30";
            break;
        case 3:
            timeDetail = "17:45";
            break;
        case 4:
            timeDetail = "19:45";
            break;
        }

        if (availSeatsDatabase.availableTimes(date, i, partySize))
        {
            cout << right << setw(2) << setfill(' ') << i << ". " << timeDetail << endl;
            canChoose[i] = true;
        }
     }   
        do {
            cout << "? ";
            timeCode = inputAnInteger(1,4);

        } while (timeCode == -1 || !canChoose[timeCode]);
    

}