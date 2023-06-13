/*All info. in one flight*/
#pragma once
#include <string>
using namespace std;
class Flight
{
public:
	Flight(string flightNo, int de, int arr,
		string deTime, string arrTime);
	void setFlightNo(string flightNo);
	string getFlightNo();
	void setDepartureAirport(int de);
	int getDepartureAirport();
	void setArrivalAirport(int arr);
	int getArrivalAirport();
	void setDepartureTime(string deTime);
	string getDepartureTime();
	void setArrivalTime(string arrTime);
	string getArrivalTime();

private:
	char flightNo[8];      // flight number
	int departureAirport;    // departure airport code
	int arrivalAirport;      // arrival airport code
	char departureTime[8]; // departure time
	char arrivalTime[8];   // arrival time

};

