#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

#include "AvailSeatsDatabase.h"

AvailSeatsDatabase::AvailSeatsDatabase()
{
   Date currentDate;
   computeCurrentDate( currentDate );

   loadAvailSeats();





}

AvailSeatsDatabase::~AvailSeatsDatabase()
{
   storeAvailSeats();
}

void AvailSeatsDatabase::decreaseAvailSeats( Date date, int timeCode, int requiredSeats )
{
   vector< AvailSeats >::iterator it = searchAvailSeats( date );

   it->setNumAvailSeats( timeCode, it->getNumAvailSeats( timeCode ) - requiredSeats );
}

bool AvailSeatsDatabase::availableTimes( Date date, int requiredSeats )
{





}

bool AvailSeatsDatabase::availableTimes( Date date, int timeCode, int requiredSeats )
{





}

vector< AvailSeats >::iterator AvailSeatsDatabase::searchAvailSeats( Date date )
{





}

//char availFileName[] = "AvailSeats - 2022-12-01.dat";
//char availFileName[] = "AvailSeats - 2023-01-29.dat";
//char availFileName[] = "AvailSeats - 2023-05-06.dat";
//char availFileName[] = "AvailSeats - 2023-05-26.dat";
char availFileName[] = "AvailSeats - 2023-06-10.dat";
//char availFileName[] = "AvailSeats - 2024-01-30.dat";
//char availFileName[] = "AvailSeats - blank.dat";

void AvailSeatsDatabase::loadAvailSeats()
{
   ifstream inSeatsFile( availFileName, ios::binary );







   inSeatsFile.close();
}

void AvailSeatsDatabase::storeAvailSeats()
{
   ofstream outSeatsFile( availFileName, ios::binary );







   outSeatsFile.close();
}