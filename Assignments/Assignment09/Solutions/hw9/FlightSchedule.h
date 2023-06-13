/*All flights*/
#pragma once
#include "Flight.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
extern const char airportName[12][12];
extern const int fullFare[12][12];
class FlightSchedule
{
public:
	FlightSchedule();
	FlightSchedule(int de, int arr);
	~FlightSchedule();
	void displayFlights(int depart, int arrive, string date);
	void getFlights(vector<Flight>& canArriveFlights);

private:
	void loadFlightSchedule();
	void loadFlightSchedule(int de, int arr);
	vector<Flight> flights;
	vector<Flight>::iterator searchFlight(string flightNo);/*used to booking, but seems not useful*/
};

