#pragma once
#include "ReservationDatabase.h";
#include "FlightSchedule.h";
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class InquiryRefund
{
public:
	InquiryRefund(ReservationDatabase& reservationDatabase, FlightSchedule& flightSchedule);
	bool bookingInquiry(string id);
	void refundApplication(string id);

private:
	ReservationDatabase& allReservations;
	FlightSchedule& allFlights;
};

