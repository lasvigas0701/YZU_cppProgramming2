#include "InquiryRefund.h"

InquiryRefund::InquiryRefund(ReservationDatabase& reservationDatabase, FlightSchedule& flightSchedule)
	: allReservations(reservationDatabase), allFlights(flightSchedule)
{
}

bool InquiryRefund::bookingInquiry(string id)
{
	vector<Reservation> reservations;
	allReservations.getReservations(reservations);
	vector<Flight> flights;
	allFlights.getFlights(flights);

	int numBooking = 1; /*output the number of bookings of aa id*/
	bool has = false;

	for (int i = 0; i < reservations.size(); i++)
	{
		/*cout << "id: " << reservations[i].getID() << endl;*/
		if (id == reservations[i].getID())
		{
			cout << numBooking << ".  ";
			allReservations.displayReservation(reservations[i], allFlights);
			cout << endl;
			has = true;
			numBooking++;
		}
	}

	if (!has)
		cout << "\nNo reservations!\n";
	return has;
}

void InquiryRefund::refundApplication(string id)
{
	if (!bookingInquiry(id))
		return;
	else
	{
		vector<Flight> flights;
		allFlights.getFlights(flights);
		vector<Reservation> reservations;
		allReservations.getReservations(reservations);

		int del;
		cout << "Enter your choice: ";
		cin >> del;

		allReservations.deleteReservation(id, del);
	}
}


