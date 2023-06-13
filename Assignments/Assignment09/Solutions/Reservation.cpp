#include "Reservation.h"
using namespace std;


Reservation::Reservation(string flightNo = "", string id = "", string name = "",
	string mobile = "", string date = "")
{
	setFlightNo(flightNo);
	setID(id);
	setName(name);
	setMobile(mobile);
	setDate(date);
}

void Reservation::setFlightNo(string flightNo)
{
	for (int i = 0; i < flightNo.size(); i++)
		this->flightNo[i] = flightNo[i];
	this->flightNo[flightNo.size()] = '\0';
}

string Reservation::getFlightNo()
{
	return flightNo;
}

void Reservation::setID(string id)
{
	for (int i = 0; i < id.size(); i++)
		this->id[i] = id[i];
	this->id[id.size()] = '\0';
}

string Reservation::getID()
{
	return id;
}

void Reservation::setName(string name)
{
	for (int i = 0; i < name.size(); i++)
		this->name[i] = name[i];
	this->name[name.size()] = '\0';
}

string Reservation::getName()
{
	return name;
}

void Reservation::setMobile(string mobile)
{
	for (int i = 0; i <= mobile.size(); i++)
		this->mobile[i] = mobile[i];
	this->mobile[mobile.size()] = '\0';
}

string Reservation::getMobile()
{
	return mobile;
}

void Reservation::setDate(string date)
{
	for (int i = 0; i < date.size(); i++)
		this->date[i] = date[i];
	this->date[date.size()] = '\0';
}

string Reservation::getDate()
{
	return date;
}

void Reservation::setTickets(int tickets[])
{
	for (int i = 1; i < 8; i++)
		this->tickets[i] = tickets[i];
}

int Reservation::getTickets(int i)
{
	return tickets[i];
}

