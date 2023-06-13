#pragma once
#include "ReservationDatabase.h";
#include "FlightSchedule.h";
extern const char airportName[12][12];
extern const int fullFare[12][12];
class MakingReservation
{
public:
	MakingReservation(ReservationDatabase& reservation, FlightSchedule& flight);
	void execute();
	void chooseArrivalAirport(int depart, int& arrive);
	void chooseFlight(Reservation& newReservation, vector<Flight> flights, int flightNum);
	void inputNumTickets(Reservation& newReservation, int& totalNum);
	void inputDetails(Reservation& newReservation);
private:
	ReservationDatabase& allReservations;
	FlightSchedule& allFlights;
};

