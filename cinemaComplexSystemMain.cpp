#include <iostream>
#include <limits>
#include <conio.h> 
#include <windows.h>  // Required for Sleep function
#include "CinemaManager.h"

using namespace std;

// Function prototypes
void ccolor(int);
void loadingbar();
bool login();

int main() {
    if (!login()) {
        cout << "Authentication failed. Exiting program..." << endl;
        return 1;
    }

    CinemaManager cinemaManager;
    ccolor(433);
     system("color 1B");
    cout <<"\n\t\t\t\t\t\tOOP Semester Project" << endl;   //cout <<" "; is used to print a output and (<< endl) to end this line.
    cout << "\n\n\n\n\n\t\t\t\tProject Title\t\t\tCinema Complex System" << endl;
    cout << "\n\t\t\t\tInstitute\t\t\tGCUF Chiniot Campus" << endl;
    cout << "\n\t\t\t\tFaculty\t\t\t\tPhysical Sciences" << endl;
    cout << "\n\t\t\t\tDepartment\t\t\tComputer Science" << endl;
    cout << "\n\t\t\t\tInstructor\t\t\tWaqar Hussain" << endl;
    cout << "\n\t\t\t\tDeveloped By  \t\t\tUmer Jahangir" << endl;
     cout << "\n\n\n\n\n\t\t\t\t\tWelcome to the Cinema Management System!" << endl;
    cout << "\n\n\n\n\n\t\t\t\t\tThis program helps you manage movies, employees, customer reservations and tickets." << endl;
    cout <<  "\n\n\n\n\n\t\t\t\t\tPress Enter to Continue......" << endl;
       
    cin.get();            
    cin.get(); 
    system("cls");  

    int choice;
    do {
    	
    	system("color 1F");
    	ccolor(929);
        system("cls");
        cout << "\n\n\n\t\t\t\t\t\t\tMain Menu" << endl;
        cout<<"\t\t\t\t\t\t********************************"<<endl;
        cout << "\t\t\t\t\t\t1. Movie Management" << endl;
        cout << "\t\t\t\t\t\t2. Employee Management" << endl;
        cout << "\t\t\t\t\t\t3. Customer Reservation System" << endl;
        cout << "\t\t\t\t\t\t4. Customer Ticket System" << endl;
        cout << "\t\t\t\t\t\t5. Exit" << endl;
        cout<<"\t\t\t\t\t\t*********************************"<<endl;
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 5 || cin.fail()) {
            cout << "Please enter a valid choice." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            switch (choice) {
                case 1:
                    system("cls");
                    cinemaManager.displayMovieManagement();
                    break;
                case 2:
                    system("cls");
                    cinemaManager.displayEmployeeManagement();
                    break;
                case 3:
                    system("cls");
                    cinemaManager.displayCustomerReservationSystem();
                    break;
                case 4:
                    system("cls");
                    cinemaManager.displayTicketManagement();
                    break;
                case 5:
                    cout << "Exiting program..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter again." << endl;
                    break;
            }
        }
    } while (choice != 5);

    return 0;
}

void ccolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    // You can use this function to display colorful content.
}

void loadingbar() {
    for (int i=15;i<=100;i+=5)//increasing by  5 and start with 15
        {
        system("cls");
        ccolor(14);
		cout<<"\n\n\n\n\n\n\n\t\t\t\n\n\n\t\t\t\n\n\n\t\t\t";
		cout<<i<<" %% Loading...\n\n\n\n\n\t\t\t\t\t";
		cout<<" ";
		for (int j=0; j<i;j+=2){
			cout<<" ";
		}
		Sleep(50);  //sleep for 50 mile second
		if(i==90 || i==50 || i==96 || i==83){
			Sleep(50);
		}
	}
	system("cls");// clear the terminal
}

bool login() {
	ccolor(14);
    const string validUsername = "umer";
    const string validPassword = "123";

    string enteredUsername, enteredPassword;
    cout<<"\n\n\n\n\n\n\n\t\t\t\n\n\n\t\t\t\n\n\n\t\t\t\t\t\t";
    cout<<"***********************"<<endl;
    cout << "\t\t\t\t\t\t\tPlease log in.\n\t\t\t\t\t\t***********************\n\n\n\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t\tUsername: ";
    cin >> enteredUsername;

    cout << "\n\t\t\t\t\t\tPassword: ";
    cin >> enteredPassword;

    if (enteredUsername == validUsername && enteredPassword == validPassword) {
        cout << "\n\t\t\t\t\t\tLogin successful. Welcome, " << "MR.UMER JAHANGIR"<< "!" << endl;
        cin.get();
        loadingbar();  // Simulating a loading bar after successful login
        return true;
    } else {
        cout << "\n\t\t\t\t\t\tLogin failed. Incorrect username or password." << endl;
        return false;
    }
}
