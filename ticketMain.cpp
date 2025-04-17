#include "TicketGenerator.h" 

#include <iostream>

using namespace std;
int main() {
    ofstream outputFile("tickets.txt", ios::app); // Open file in append mode
    if (!outputFile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    TicketGenerator ticketGen;
    char choice;

    do {
    	system("cls");
        Ticket ticket = ticketGen.generateTicket();
        system("cls");
        cout << "Ticket generated successfully!" << endl;
        cout << "Customer Name: " << ticket.getName() << endl;
        cout << "Movie: " << ticket.getMovie() << endl;
        cout << "Hall: " << ticket.getHall() << endl;
        cout << "Seat: " << ticket.getSeat() << endl;
        cout << "Ticket ID: " << ticket.getTicketId() << endl;
        cout << "Price: $" << ticket.getPrice() << endl;

        ticket.writeToStream(outputFile); // Write ticket details to the file

        cout << "Would you like to generate another ticket? (y/n): ";
        cin >> choice;

        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');

    outputFile.close(); // Close the file
    cout << "Thank you for using the ticket generator!" << endl;

    return 0;
}
