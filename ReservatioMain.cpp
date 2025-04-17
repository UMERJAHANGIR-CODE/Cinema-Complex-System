#include<iostream>
#include "Reservation.h" // Assuming Reservation class is declared in reservation.h
#include "movieManager.h" 
using namespace std;
int main() 
{
    Reservation reservation; // Create an instance of the Reservation class
    vector<MovieSlot> movieSlots;
    vector<Movie> movieList;
    int choice;
    string searchName;

    do {
        system("cls");
        cout << "=== Customer Reservation System ===" << endl;
        cout << "1. Display Customer List" << endl;
        cout << "2. Register a Customer" << endl;
        cout << "3. Search for a Customer" << endl;
        cout << "4. Delete a Customer" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
         	 if (choice < 1 || choice > 8 || cin.fail()) {
                cout << "Please enter a valid choice." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else {
        switch (choice) {
            case 1:
                system("cls");
                reservation.displayCustomerList();
                cin.get();
                break;

            case 2:
                system("cls");
                reservation.registerCustomer(movieSlots, movieList);
                cin.get();
                break;

            case 3:
                system("cls");
                cout << "Enter customer name to search: ";
                getline(cin, searchName);
                reservation.searchCustomerByName(searchName);
                cin.get();
                break;

            case 4:
                system("cls");
                cout << "Enter customer name to delete: ";
                getline(cin, searchName);
                reservation.deleteCustomer(searchName);
                cin.get();
                break;

            case 5:
                system("cls");
                cout << "Exiting program." << endl;
                cin.get();
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    } while (choice != 5);

    return 0;
}
