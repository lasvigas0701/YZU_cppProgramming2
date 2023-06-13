/*All reservations*/
#pragma once
#include "Reservation.h"
#include <vector>
#include <string>
using namespace std;
extern const char airportName[12][12];
extern const int fullFare[12][12];
extern const int discount[8];
class ReservationDatabase
{
public:
	ReservationDatabase(); /*load reservation.dat*/
	~ReservationDatabase(); /*write in reservation.dat*/
	void displayReservation(Reservation reservation, FlightSchedule allFlights); /*display the info. of specific reservation*/
	void addReservation(Reservation newRes); /*reservations.push_back*/
	void deleteReservation(string id, int reservationNumber); /*delete(erase) one reservation*/
	void getReservations(vector<Reservation>& allReservation);
private:
	void loadReservations();
	void storeReservations();
	vector<Reservation> reservations; /*each index is a reservation info.*/
	vector<Reservation>::iterator searchReservation(string id, int reservationNumber); /*called by deleteReservation*/
};

