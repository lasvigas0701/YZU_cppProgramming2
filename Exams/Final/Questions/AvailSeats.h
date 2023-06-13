#ifndef AVAIL_SEATS_H
#define AVAIL_SEATS_H

#include "Date.h"

class AvailSeats
{
public:
   AvailSeats();
   AvailSeats( Date theDate, int *theNumAvailSeats );

   void setDate( Date theDate );
   void setNumAvailSeats( int timeCode, int theNumAvailSeats );

   Date getDate();
   int getNumAvailSeats( int timeCode );

private:
   Date date;
   int numAvailSeats[ 5 ]; // number of available seats
   // numAvailSeats[ 0 ] : not used
   // numAvailSeats[ 1 ] : number of available seats for 11:30
   // numAvailSeats[ 2 ] : number of available seats for 13:30
   // numAvailSeats[ 3 ] : number of available seats for 17:45
   // numAvailSeats[ 4 ] : number of available seats for 19:45
};

#endif