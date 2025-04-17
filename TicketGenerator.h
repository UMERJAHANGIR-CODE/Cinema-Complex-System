#ifndef TICKETGENERATOR_H
#define TICKETGENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "Reservation.h"
using namespace std;

class Ticket {
private:
    string name;
    string movie;
    string hall;
    string seat;
    int ticketId;
    float price;

public:
    Ticket(string name, string movie, string hall, string seat, int ticketId, float price)
        : name(name), movie(movie), hall(hall), seat(seat), ticketId(ticketId), price(price) {}
         bool isSeatReserved() const {
        return Reservation::isSeatReserved(seat);
    }

    string getName() const { return name; }
    string getMovie() const { return movie; }
    string getHall() const { return hall; }
    string getSeat() const { return seat; }
    int getTicketId() const { return ticketId; }
    float getPrice() const { return price; }

    void writeToStream(ofstream &file) {
        file << "Customer Name: " << name << endl;
        file << "Movie: " << movie << endl;
        file << "Hall: " << hall << endl;
        file << "Seat: " << seat << endl;
        file << "Ticket ID: " << ticketId << endl;
        file << "Price: $" << price << endl;
        file << "---------------------" << endl;
    }
};

class TicketGenerator {
private:
    unordered_set<string> reservedSeats;
     vector<Ticket> tickets;
public:
    Ticket generateTicket() {
        string name, movie, hall, desiredSeat;
        int ticketId;
        float price;
        bool validInput = false;

        while (!validInput) {
            cout << "Enter customer name: ";
            getline(cin >> ws, name);

            cout << "Enter movie: ";
            getline(cin >> ws, movie);

            cout << "Enter hall: ";
            getline(cin >> ws, hall);

            cout << "Enter desired seat: ";
            getline(cin >> ws, desiredSeat);

            cout << "Enter ticket ID: ";
            cin >> ticketId;

            cout << "Enter price: ";
            cin >> price;
cout << "Ticket has been generated." << endl;
            if (name.empty() || movie.empty() || hall.empty() || desiredSeat.empty() || ticketId <= 0 || price <= 0) {
                cout << "Invalid input. All attributes must be filled, and ID and price should be positive values." << endl;
            } else if (!checkSeatAvailability(desiredSeat)) {
                cout << "Seat " << desiredSeat << " is already taken. Please choose another seat." << endl;
            } else {
                validInput = true;
            }

            // Clear input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            reservedSeats.insert(desiredSeat);
        Ticket newTicket(name, movie, hall, desiredSeat, ticketId, price);
        tickets.push_back(newTicket);  // Add the generated ticket to the vector
        return newTicket;
        }

        reservedSeats.insert(desiredSeat);
        return Ticket(name, movie, hall, desiredSeat, ticketId, price);
    }

    bool checkSeatAvailability(string seat) const {
        return reservedSeats.find(seat) == reservedSeats.end();
    }
    void displayAllTickets() const {
        if (tickets.empty()) {
            cout << "No tickets to display." << endl;
            return;
        }

        cout << "All Tickets:" << endl;
        for (const auto& ticket : tickets) {
            cout << "---------------------" << endl;
            cout << "Customer Name: " << ticket.getName() << endl;
            cout << "Movie: " << ticket.getMovie() << endl;
            cout << "Hall: " << ticket.getHall() << endl;
            cout << "Seat: " << ticket.getSeat() << endl;
            cout << "Ticket ID: " << ticket.getTicketId() << endl;
            cout << "Price: $" << ticket.getPrice() << endl;
        }
        cout << "---------------------" << endl;
    }

    bool deleteTicket(int ticketId) {
        auto it = find_if(tickets.begin(), tickets.end(), [ticketId](const Ticket& t) {
            return t.getTicketId() == ticketId;
        });

        if (it != tickets.end()) {
            reservedSeats.erase(it->getSeat());
            tickets.erase(it);
            cout << "Ticket with ID " << ticketId << " deleted successfully." << endl;
            return true;
        } else {
            cout << "Ticket with ID " << ticketId << " not found." << endl;
            return false;
        }
    }
};
#endif