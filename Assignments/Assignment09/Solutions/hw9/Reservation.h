/*All info. in one reservation*/
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "FlightSchedule.h"
class Reservation
{
public:
	Reservation(string flightNo, string id, string name, 
				string mobile, string date);
	void setFlightNo(string flightNo);
	string getFlightNo();
	void setID(string id);
	string getID();
	void setName(string name);
	string getName();
	void setMobile(string mobile);
	string getMobile();
	void setDate(string date);
	string getDate();
	void setTickets(int tickets[]);
	int getTickets(int i);
	/*void displayReservationDetails(FlightSchedule allFlight); called by displayReservation but details are private*/

private:
	char flightNo[8]; // flight number
	char id[12];      // ID number
	char name[8];     // name
	char mobile[12];  // mobile phone number
	char date[12];    // departure date
	int tickets[8];
};

