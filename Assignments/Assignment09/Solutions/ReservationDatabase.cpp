#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase()
{
	loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
	storeReservations();
}

void ReservationDatabase::displayReservation(Reservation reservation, FlightSchedule allFlight)
{
    cout << "Ticket information:\n\n";
    cout << "Date: " << reservation.getDate() << endl;
    cout << "Flight: B7-" << reservation.getFlightNo() << endl << endl;

    vector<Flight> flights;
    allFlight.getFlights(flights);
    int k = 0;
    for (; k < flights.size(); k++)
        if (flights[k].getFlightNo() == reservation.getFlightNo())
            break;

    int departureAirport = flights[k].getDepartureAirport();
    int arrivalAirport = flights[k].getArrivalAirport();

    cout << setw(9) << right << airportName[departureAirport] << " -> "
        << setw(9) << left << airportName[arrivalAirport] << endl;

    cout << setw(9) << right << flights[k].getDepartureTime() << "    ";
    cout << setw(9) << left << flights[k].getArrivalTime() << endl << endl;

    char ticketType[8][24] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                       "Senior Citizen Fare",     "Impaired Fare",
                                       "Impaired Companion Fare", "Military Fare" };

    int total = 0;
    int fare;
    for (int i = 1; i <= 7; i++)
        if (reservation.getTickets(i) > 0)
        {
            fare = fullFare[departureAirport][arrivalAirport] * discount[i] / 100;
            total += (fare * reservation.getTickets(i));
            cout << right << setw(23) << ticketType[i] << "  TWD "
                << setw(4) << fare << " x " << reservation.getTickets(i) << endl;
        }

    cout << "\nTotal: " << total << endl;
}

void ReservationDatabase::addReservation(Reservation newRes)
{
    reservations.push_back(newRes);
}

void ReservationDatabase::deleteReservation(string id, int reservationNumber)
{
    vector<Reservation>::iterator it = searchReservation(id, reservationNumber);
    if (it == reservations.end())
        return;
    reservations.erase(it);
    cout << "\nThe seleted booking has been deleted. \n";
}

void ReservationDatabase::getReservations(vector<Reservation>& allReservation)
{
    for (size_t i = 0; i < reservations.size(); i++)
        allReservation.push_back(reservations[i]);
}

void ReservationDatabase::loadReservations()
{
    ifstream loadRes("Reservations.dat", ios::in | ios::binary);

    if (!loadRes) {
        cerr << "Reservations.dat in loadReservations cannot be opened!";
        exit(1);
    }

    loadRes.seekg(0, ios::end);
    int numReservations = (static_cast<int>(loadRes.tellg()) / sizeof(Reservation));
    loadRes.seekg(0, ios::beg);
    Reservation temp("", "", "", "", "");
    for (int i = 0; i < numReservations; i++) {
        loadRes.read(reinterpret_cast<char*>(&temp), sizeof(Reservation));
        reservations.push_back(temp);
    }
    loadRes.clear();
    loadRes.close();
}

void ReservationDatabase::storeReservations()
{
    ofstream writeRes("Reservations.dat", ios::out | ios::binary);

    if (!writeRes) {
        cerr << "Reservations.dat in f(saveReservation) cannot be opened!\n";
        exit(1);
    }

    writeRes.seekp(0, ios::beg);
    /*cout << "rs: " << reservations.size() << endl;*/
    for (size_t i = 0; i < reservations.size(); i++)
        writeRes.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));

    writeRes.clear();
    writeRes.close();
}

vector<Reservation>::iterator ReservationDatabase::searchReservation(string id, int reservationNumber)
{
    int temp = 0;
    for (vector<Reservation>::iterator it = reservations.begin(); it != reservations.end(); it++)
    {
        if (it->getID() == id)
        {
            temp++;
            if (temp == reservationNumber)
                return it;
        }
    }
    return reservations.end();
}

