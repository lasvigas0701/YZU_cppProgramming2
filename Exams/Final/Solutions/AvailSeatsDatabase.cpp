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
	int count = 31;
	/*for (int i = 0; i < availSeats.size(); i++)
	{
		if (availSeats[i].getDate() < currentDate)
		{
			count++;
		}
		else
			break;
	}*/
	if (availSeats.empty())
	{
		for (int i = 0; i < 31; i++)
		{
			int newNum[5] = { 0, 20, 20, 20, 20 };
			AvailSeats newData((currentDate + i), newNum);
			availSeats.push_back(newData);
		}
	}
	else
	{
		vector<AvailSeats>::iterator it = availSeats.begin();
		while (!availSeats.empty() && it->getDate() < currentDate)
		{
			it = availSeats.erase(it);
			count--;
		}
		for (int i = count; i < 31; i++)
		{
			int newNum[5] = { 0, 20, 20, 20, 20 };
			AvailSeats newData((currentDate + i), newNum);
			availSeats.push_back(newData);
		}
	}

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
	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	bool have = false;
	for (int i = 1; i < 5; i++)
	{
		if (availableTimes(it->getDate(), i, requiredSeats))
			have = true;
	}

	return have;
}

bool AvailSeatsDatabase::availableTimes( Date date, int timeCode, int requiredSeats )
{
	vector< AvailSeats >::iterator it = searchAvailSeats(date);

	if (it->getNumAvailSeats(timeCode) >= requiredSeats)
		return true;

	return false;
}

vector< AvailSeats >::iterator AvailSeatsDatabase::searchAvailSeats( Date date )
{
	vector< AvailSeats >::iterator it = availSeats.begin();
	for (; it != availSeats.end(); it++)
	{
		if (it->getDate() == date)
			break;
	}

	return it;
}

//char availFileName[] = "AvailSeats-2022-12-01.dat";
//char availFileName[] = "AvailSeats-2023-01-29.dat";
//char availFileName[] = "AvailSeats-2023-05-06.dat";
//char availFileName[] = "AvailSeats-2023-05-26.dat";
char availFileName[] = "AvailSeats-2023-06-10.dat";
//char availFileName[] = "AvailSeats-2024-01-30.dat";
//char availFileName[] = "AvailSeats - blank.dat";

void AvailSeatsDatabase::loadAvailSeats()
{
	ifstream inSeatsFile( availFileName, ios::binary );

	if (!inSeatsFile)
	{
		cerr << "\navailFile could not be opened!\n";
		exit(1);
	}

	inSeatsFile.seekg(0, ios::end);
	size_t numSeatsFile = inSeatsFile.tellg() / sizeof(AvailSeats);
	inSeatsFile.seekg(0, ios::beg);

	AvailSeats buf;
	for (int i = 0; i < numSeatsFile; i++)
	{
		inSeatsFile.read(reinterpret_cast<char*>(&buf), sizeof(AvailSeats));
		availSeats.push_back(buf);
		/*cout << buf.getDate().getDay() << ":" << buf.getNumAvailSeats(1) << " " << buf.getNumAvailSeats(2) << " "
			<< buf.getNumAvailSeats(3) << " " << buf.getNumAvailSeats(4) << " " << endl;*/
	}

	inSeatsFile.close();
}

void AvailSeatsDatabase::storeAvailSeats()
{
	ofstream outSeatsFile( availFileName, ios::binary );

	if (!outSeatsFile)
	{
		cerr << "\navailFileName could not be opened!\n";
		exit(1);
	}

	for (int i = 0; i < availSeats.size(); i++)
	{
		outSeatsFile.write(reinterpret_cast<const char*>(&availSeats[i]), sizeof(AvailSeats));
	}

	outSeatsFile.close();
}