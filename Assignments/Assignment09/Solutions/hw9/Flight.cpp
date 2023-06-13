#include "Flight.h"

Flight::Flight(string flightNo = "", int de = 0, int arr = 0,
	string deTime = "", string arrTime = "")
{
	setFlightNo(flightNo);
	setDepartureAirport(de);
	setArrivalAirport(arr);
	setDepartureTime(deTime);
	setArrivalTime(arrTime);
}

void Flight::setFlightNo(string flightNo)
{
	for (int i = 0; i < flightNo.size(); i++)
		this->flightNo[i] = flightNo[i];
	this->flightNo[flightNo.size()] = '\0';
}

string Flight::getFlightNo()
{
	return flightNo;
}

void Flight::setDepartureAirport(int de)
{
	this->departureAirport = de;
}

int Flight::getDepartureAirport()
{
	return departureAirport;
}

void Flight::setArrivalAirport(int arr)
{
	this->arrivalAirport = arr;
}

int Flight::getArrivalAirport()
{
	return arrivalAirport;
}

void Flight::setDepartureTime(string deTime)
{
	for (int i = 0; i < deTime.size(); i++)
		this->departureTime[i] = deTime[i];
	this->arrivalTime[deTime.size()] = '\0';
}

string Flight::getDepartureTime()
{
	return departureTime;
}

void Flight::setArrivalTime(string arrTime)
{
	for (int i = 0; i < arrTime.size(); i++)
		this->arrivalTime[i] = arrTime[i];
	this->arrivalTime[arrTime.size()] = '\0';
}

string Flight::getArrivalTime()
{
	return arrivalTime;
}