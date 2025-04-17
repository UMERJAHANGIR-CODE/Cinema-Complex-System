#ifndef RESERVATION_H  // Header guard to prevent multiple inclusions
#define RESERVATION_H

#include "MovieManager.h" 

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>  
#include <ctime>
#include <sstream>
#include <fstream>
#include<set>
#include<limits>
#include<memory>
#include <unordered_set>
using namespace std;
class Customer {
public:
    string ID; 
    string name;
    int age;
    string seat;
    string hall;
    double price;
    struct Date {
        int day;
        int month;
        int year;
    } 
	entryDate,
	arriveDate,
	exitDate;
	 string customerName;
	 string movieName;
   time_t registerTime;

   time_t deletedTime;

	// Default constructor
    Customer() :  ID(""), name(""), age(0), price(0.0),seat(""),hall(""), registerTime(0),deletedTime(0) {}
};
// Forward declaration if needed


class Reservation 
{
private:
    vector<Customer> CustomerList;
    vector<Customer> deletedCustomer;
    
  vector<MovieSlot> movieList;
 static unordered_set<string> reservedSeats;
public:
	 static bool isSeatReserved(const string& seat);
    static void reserveSeat(const string& seat);
    void displayCustomerList()
	 {    	
	 int totalCustomers = CustomerList.size(); // Total number of employees
    if (CustomerList.empty()) 
	{
        cout << "No Customer available." << endl;
        
    }
	 else
	  {
        cout << "#################################################################################" << endl;
        cout<< '|'<<setw(25)<<" Customer ID"<<'|'
		        << setw(30) << "Customer Name" << '|'
                    << setw(10) << "Age" << '|'
                    << setw(10) << "Reserve hall" << '|'
                    << setw(10) << "Movie Name" << '|'
                    << setw(10) << "Reserve seat" << '|'
                    << setw(10) << "Price" << '|'
                    << setw(6) << "Entery. Date" << '|'
					<< setw(10) << "Arrival. Date" << '|'
                    << setw(10) << "Exp. Date" << '|'<<endl;
        cout << "#################################################################################" <<endl;

        for (const auto& customer : CustomerList)
		 {
             cout << '|'<<setw(40)<<customer.ID<< '|'
			            << setw(30) << customer.name << '|'
                        << setw(10) << customer.age << '|'
                        << setw(30) << customer.hall << '|'
                        << setw(10) << customer.seat << '|'
                        << setw(5) << customer.price << '|' 
                        << setw(10) << customer.entryDate.day<<" D " << '/' 
                        << setw(2) << customer.entryDate.month<<" M "<< '/'
                        << setw(4) << customer.entryDate.year  <<" Y "<< '|'
                        << setw(10) << customer.arriveDate.day<<" D " << '/'
                        << setw(2) << customer.arriveDate.month<<" M " << '/'
                        << setw(4) << customer.arriveDate.year <<" Y " << '|'
                       << setw(10) << customer.exitDate.day<<" D " << '/'
                        << setw(2) << customer.exitDate.month<<" M " << '/'
                        << setw(4) << customer.exitDate.year <<" Y " << '|'<<endl;
						cout << "Customer was registered at: " << ctime(&customer.registerTime); // Display registered time
					   
						  // Display registered time
              
        
        cout << "#####################################################################" << endl;
    }
    cout << "Total Customers: " << totalCustomers << endl;
}

}


void registerCustomer(vector<MovieSlot>& movieSlots, vector<Movie>& movieList) {
    char registerAnother;
    do{
	
        Customer newCustomer;
        newCustomer.registerTime = time(0); // Record the registration time

        cout << "Customer register time: " << ctime(&newCustomer.registerTime) << endl;
        
      cout << "Enter Customer ID: ";
do {
    if (getline(cin, newCustomer.ID)) {
        if (newCustomer.ID.empty()) {
            cout << "Please enter any Customer ID: ";
        } else {
            auto it = find_if(CustomerList.begin(), CustomerList.end(),
                              [&newCustomer](const Customer& customer) { return customer.ID == newCustomer.ID; });

            if (it != CustomerList.end()) {
                cout << "A customer with ID " << newCustomer.ID << " already exists." << endl;
                string choice;
                cout << "Do you want to change the ID? (Y/N): ";
                cin >> choice;
                if (choice == "Y" || choice == "y") {
                    cout << "Enter new Customer ID: ";
                    cin.ignore();
                    getline(cin, newCustomer.ID);
                } else {
                    return; // Abort the registration process
                }
            } else {
                break;
            }
        }
    }
} while (newCustomer.ID.empty());

// Continue similarly for other customer details...


        cout << "Enter customer name: ";
        do {
            if (getline(cin, newCustomer.name)) {
                if (newCustomer.name.empty()) {
                    cout << "Please enter any name: ";
                } else {
                    break;
                }
            }
        } while (newCustomer.name.empty());


cout << "Enter customer age: ";
do {
    if (!(cin >> newCustomer.age)) {
        cout << "Please enter a valid age." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        break;
    }
} while (true);

cout << "Enter reserved hall: ";
do {
    if (getline(cin, newCustomer.hall)) {
        if (newCustomer.hall.empty()) {
            cout << "Please enter the reserved hall: ";
        } else {
            break;
        }
    }
} while (newCustomer.hall.empty());

 string movieName;
    bool validMovie = false;

    do {
        cout << "Enter movie name: ";
        getline(cin, movieName);

        auto movieIt = find_if(movieList.begin(), movieList.end(),
                               [&movieName](const Movie& movie) { return movie.name == movieName; });

        if (movieIt == movieList.end()) {
            cout << "Invalid movie. This movie is not available." << endl;
            char choice;
            cout << "Do you want to enter another movie? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                break; // If the user doesn't want to enter another movie, break the loop
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            validMovie = true;
        }
    } while (!validMovie);

    if (validMovie) {
        // Associate the customer with the selected movie
        Customer newCustomer;
        newCustomer.movieName = movieName;
    }

  // Loop through movie slots
        for (size_t i = 0; i < movieSlots.size(); ++i) {
            cout << "Slot " << i + 1 << " details: " << endl;
            cout << "Movie: " << movieSlots[i].movieName << endl;
            
            // Access other slot details as needed
        }

        bool seatValid = false;

        do {
            string reservedSeat;
            cout << "Enter reserved seat: ";
            getline(cin, reservedSeat);

            if (reservedSeat.empty()) {
                cout << "Please enter the reserved seat: ";
            } else {
                auto it = find_if(CustomerList.begin(), CustomerList.end(),
                                  [&reservedSeat](const Customer& customer) { return customer.seat == reservedSeat; });

                if (it != CustomerList.end()) {
                    cout << "This seat is already reserved for " << it->customerName << "." << endl;
                    string choice;
                    cout << "Do you want to change the seat? (Y/N): ";
                    cin >> choice;

                    if (choice == "Y" || choice == "y") {
                        cout << "Enter new reserved seat: ";
                        cin.ignore();
                    } else {
                        return; // Abort the registration process
                    }
                } 
            
                 seatValid = true; // Seat is reserved
                }
            
        } while (!seatValid);

 
string choice;

int entryDay, entryMonth, entryYear;
do { 
       cout << "Do you want to proceed with the Entery Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	 newCustomer.entryDate.day = 0;
                newCustomer.entryDate.month = 0;
                newCustomer.entryDate.year = 0;
            break;
        } else if (choice == "Y" || choice == "y") {
        	cout << "Enter entry date (DD MM YYYY): ";
    cin >> entryDay >> entryMonth >> entryYear;

    if (cin.fail() || entryDay < 1 || entryDay > 31 || entryMonth < 1 || entryMonth > 12 || entryYear < 1900 || entryYear > 2100) {
        cout << "Invalid date entered. Please enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        newCustomer.entryDate.day = entryDay;
        newCustomer.entryDate.month = entryMonth;
        newCustomer.entryDate.year = entryYear;
        break;
    }
}
 else {
            cout << "Invalid choice. Please enter Y or N." << endl;
        }
} while (true);


int arriveDay, arriveMonth, arriveYear;
do {
	 cout << "Do you want to proceed with Arrival the  Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	newCustomer.arriveDate.day = 0;
                 newCustomer.arriveDate.month = 0;
              newCustomer.arriveDate.year = 0;
            break;
        } else if (choice == "Y" || choice == "y") {
        	cout << "Enter arrival date (DD MM YYYY): ";
    cin >> arriveDay >> arriveMonth >> arriveYear;

    if (cin.fail() || arriveDay < 1 || arriveDay > 31 || arriveMonth < 1 || arriveMonth > 12 || arriveYear < 1900 || arriveYear > 2100) {
        cout << "Invalid date entered. Please enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        newCustomer.arriveDate.day = arriveDay;
        newCustomer.arriveDate.month = arriveMonth;
        newCustomer.arriveDate.year = arriveYear;
        break;
    }
	}
	 else {
            cout << "Invalid choice. Please enter Y or N." << endl;
        }
} while (true);


int exitDay, exitMonth, exitYear;
do {
	cout << "Do you want to proceed with Expiry  Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	  newCustomer.exitDate.day = 0;
                newCustomer.exitDate.month = 0;
               newCustomer.exitDate.year = 0;
            break;
        } else if (choice == "Y" || choice == "y") {
        cout << "Enter expiry date (DD MM YYYY): ";
    cin >> exitDay >> exitMonth >> exitYear;

    if (cin.fail() || exitDay < 1 || exitDay > 31 || exitMonth < 1 || exitMonth > 12 || exitYear < 1900 || exitYear > 2100) {
        cout << "Invalid date entered. Please enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        newCustomer.exitDate.day = exitDay;
        newCustomer.exitDate.month = exitMonth;
        newCustomer.exitDate.year = exitYear;
        break;
    }
}
     else {
            cout << "Invalid choice. Please enter Y or N." << endl;
        }
} while (true);
        newCustomer.registerTime = time(0); 
        // Add the new customer to the CustomerList vector
        CustomerList.push_back(newCustomer);

        ofstream outputFile("Registered_customers.txt", ios::app); // Open in append mode

    if (outputFile.is_open()) {
        // Write the customer details to the file
        outputFile << "Customer ID: " << newCustomer.ID << endl;
        outputFile << "Customer Name: " << newCustomer.name << endl;
        outputFile << "Age: " << newCustomer.age << endl;
        outputFile << "Reserved Hall: " << newCustomer.hall << endl;
        outputFile << "Reserved Movie: " << movieName << endl;
        outputFile << "Reserved Seat: " << newCustomer.seat << endl;
        outputFile << "Entry Date: " << newCustomer.entryDate.day << "/" << newCustomer.entryDate.month << "/" << newCustomer.entryDate.year << endl;
        outputFile << "Arrival Date: " << newCustomer.arriveDate.day << "/" << newCustomer.arriveDate.month << "/" << newCustomer.arriveDate.year << endl;
        outputFile << "Exit Date: " << newCustomer.exitDate.day << "/" << newCustomer.exitDate.month << "/" << newCustomer.exitDate.year << endl;
        outputFile << "Registered Time: " << ctime(&newCustomer.registerTime);
        outputFile << "-----------------------------" << endl;

        // Close the file
        outputFile.close();

        cout << "Customer details saved to file successfully!" << endl;
        cin.get();
    } else {
        cout << "Unable to open the file!" << endl;
    }


        cout << "Customer details registered successfully!" << endl;
        cin.get();
        
          system("cls");
        cout << "Do you want to register another customer? (Y/N): ";
        cin >> registerAnother;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (registerAnother == 'N' || registerAnother == 'n') {
            break; // Exit the loop if the user doesn't want to register another customer
        }
    

	} while (true);
}

void searchCustomerByName(string& customerName) {
    while (true) {
        bool found = false;

        for (const auto& customer : CustomerList) {
            if (customer.name == customerName) {
                found = true;
                // Display customer details
                cout << "Customer found:" << endl;
                cout << "Customer Name: " << customer.name << endl;
                cout << "Customer ID: " << customer.ID << endl;
                cout << "Age: " << customer.age << endl;
                cout << "Reserved Hall: " << customer.hall << endl;
                cout << "Reserved Seat: " << customer.seat << endl;
                cout << "Entry Date: " << customer.entryDate.day << "/" << customer.entryDate.month << "/" << customer.entryDate.year << endl;
                cout << "Arrival Date: " << customer.arriveDate.day << "/" << customer.arriveDate.month << "/" << customer.arriveDate.year << endl;
                cout << "Exit Date: " << customer.exitDate.day << "/" << customer.exitDate.month << "/" << customer.exitDate.year << endl;
                cout << "Registered Time: " << ctime(&customer.registerTime);
                if (customer.deletedTime != 0) {
                    cout << "Deleted Time: " << ctime(&customer.deletedTime) << endl;
                } else {
                    cout << "Customer has not been deleted." << endl;
                }
            }
        }

        if (!found) {
            cout << "Customer not found." << endl;
            cin.get();
        }

        cout << "-----------------------------" << endl;
        cout << "Do you want to search for another customer? (Y/N): ";
        char searchAgain;
        cin >> searchAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (searchAgain == 'N' || searchAgain == 'n') {
            break; // Exit the outer loop if the user doesn't want to search again
        } else {
            cout << "Enter Customer Name to search: ";
            getline(cin, customerName);
        } 
    }
}
void deleteCustomer(string& customerName) {
    while (true) {
        auto it = find_if(CustomerList.begin(), CustomerList.end(),
                          [&customerName](const Customer& customer) { return customer.name == customerName; });

        if (it != CustomerList.end()) {
            time_t currentTime = time(0);
            it->deletedTime = currentTime;
            deletedCustomer.push_back(*it);
            CustomerList.erase(it);

            cout << "Customer '" << customerName << "' deleted successfully." << endl;
            cout << "Deleted Time: " << ctime(&currentTime) << endl;

            cout << "Do you want to delete another customer? (Y/N): ";
            char searchAgain;
            cin >> searchAgain;

            if (searchAgain == 'N' || searchAgain == 'n') {
                break; // Exit the outer loop if the user doesn't want to search again
            } else {
                cout << "Enter Customer Name to Delete: ";
                cin.ignore(); // Clear input buffer
                getline(cin, customerName);
                continue; // Jump back to the beginning of the outer loop to search again
            }

            ofstream outputFile("C:/Users/Hassan/Desktop/Deleted_customers.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << "Customer Name: " << customerName << endl;
                outputFile << "Deleted Time: " << ctime(&currentTime) << endl;
                outputFile << "-----------------------------" << endl;
                outputFile.close();

                cout << "Customer details deleted from file successfully!" << endl;
                break; // Exit the loop after successful deletion
            } else {
                cout << "Unable to open the file!" << endl;
            }
        } else {
            cout << "Customer '" << customerName << "' not found in the list." << endl;
            char retryChoice;
            cout << "Do you want to delete another customer? (Y/N): ";
            cin >> retryChoice;

            if (retryChoice == 'N' || retryChoice == 'n') {
                break; // Exit the loop if the user doesn't want to delete another customer
            } else {
                cout << "Enter Customer Name to delete: ";
                cin.ignore(); // Clear input buffer
                getline(cin, customerName);
            }
        }
    }
}

void cancelReservation() {
    do {
        if (CustomerList.empty()) {
            cout << "No reservations available to cancel." << endl;
            break;
        }

        cout << "Current reservations: " << endl;
        cout << "---------------------" << endl;

        for (const auto& customer : CustomerList) {
            cout << "Customer ID: " << customer.ID << " - Customer Name: " << customer.name << endl;
        }

        string customerID;
        cout << "\nEnter Customer ID to cancel reservation: ";
        cin >> customerID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto it = find_if(CustomerList.begin(), CustomerList.end(),
                          [&customerID](const Customer& customer) { return customer.ID == customerID; });

        if (it != CustomerList.end()) {
            time_t currentTime = time(0);
            it->deletedTime = currentTime;
            deletedCustomer.push_back(*it);
            CustomerList.erase(it);

            cout << "Reservation for Customer ID '" << customerID << "' ("
                 << it->name << ") canceled successfully." << endl;
            cout << "Canceled Time: " << ctime(&currentTime) << endl;

            // You can also write the details of the canceled reservation to a file here if needed

        } else {
            cout << "Reservation for Customer ID '" << customerID << "' not found." << endl;
        }

        char cancelAnother;
        cout << "Do you want to cancel another reservation? (Y/N): ";
        cin >> cancelAnother;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cancelAnother != 'Y' && cancelAnother != 'y') {
            break;
        }

    } while (true);
}


};
#endif