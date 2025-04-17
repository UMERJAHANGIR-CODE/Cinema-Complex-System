// MovieManager.h - Remain the same

// CinemaManager.h

#include <iostream>
#include <vector>
#include <limits>
#include "MovieManager.h"
#include "EmployeeManager.h"
#include "reservation.h"
#include "TicketGenerator.h" 
class CinemaManager {
private:
    MovieManager movieManager;
    EmployeeManager empManager;
     Reservation reservation; // Create an instance of the Reservation class
    vector<MovieSlot> movieSlots;
    vector<Movie> movieList;
    int choice;
    string searchName;
    TicketGenerator ticketGen;
public:
    void displayMovieManagement() {
    int Choice;

    do {
        cout << "\n\n\n\t\t\t\t\t\t=== Movie Management System ===" << endl;
        cout<<"\t\t\t\t\t\t********************************"<<endl;
        cout << "\t\t\t\t\t\t1. Display Movie List" << endl;
        cout << "\t\t\t\t\t\t2. Register a Movie" << endl;
        cout << "\t\t\t\t\t\t3. Modify a Movie" << endl;
        cout << "\t\t\t\t\t\t4. Delete a Movie" << endl;
        cout << "\t\t\t\t\t\t5. Restore a Movie" << endl;
        cout << "\t\t\t\t\t\t6. Sort Movies" << endl;
        cout << "\t\t\t\t\t\t7. Search Movies" << endl;
        cout << "\t\t\t\t\t\t8. Display Movies Slot" << endl;
        cout << "\t\t\t\t\t\t9. Display All Movies" << endl;
        cout << "\t\t\t\t\t\t10. Exit" << endl;
         cout<<"\t\t\t\t\t\t*********************************"<<endl;
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> Choice;
        cin.ignore(); // Consume newline

        if (Choice < 1 || Choice > 10 || cin.fail()) {
            cout << "\t\t\t\t\t\tPlease enter a valid choice." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (Choice) {
            case 1:
                system("cls");
                // Assuming movieManager is an instance of MovieManager class
                movieManager.displayMovieList();
                cin.get();
                break;

            case 2:
                system("cls");
                movieManager.registerMovie();
                cin.get();
                break;
{

            case 3:
                system("cls");
                cout << "Enter movie name to modify: ";
                string movieName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, movieName);
                movieManager.modifyMovie(movieName);
                cin.get();
                break;
            }
{

            case 4:
                system("cls");
                cout << "Enter movie name to delete: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string deleteName;
                getline(cin, deleteName);
                movieManager.deleteMovie(deleteName);
                cin.get();
                break;
}
{

            case 5:
                system("cls");
                cout << "Enter movie name to Restore: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string restoreName;
                getline(cin, restoreName);
                movieManager.restoreMovie(restoreName);
                cin.get();
                break;
}
            case 6:
                system("cls");
                int sortChoice;
                cout << "Sort movies by:" << endl;
                cout << "1. Name" << endl;
                cout << "2. Genre" << endl;
                cout << "3. Price" << endl;
                cout << "Enter your choice: ";
                cin >> sortChoice;
                cin.ignore(); // Consume newline

                if (sortChoice < 1 || sortChoice > 3 || cin.fail()) {
                    cout << "Please enter a valid choice." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                } else {
                    movieManager.sortMoviesBy(sortChoice);
                }
                cin.get();
                break;
{

            case 7:
                system("cls");
                cout << "Enter movie name to search: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string searchName;
                getline(cin, searchName);
                movieManager.searchMovieByName(searchName);
                cin.get();
                break;
}

            case 8:
                system("cls");
                movieManager.displayMovieListWithSlots();
                cin.get();
                break;
            case 9:
            	system("cls");
                movieManager.viewAllMovies();
                 cin.get();
                break;
       
            case 10:
                system("cls");
                cout << "Exiting movie management menu." << endl;
                cin.get();
                break;

            default:
                cout << "\t\t\t\t\t\tInvalid choice. Please try again." << endl;
                break;
        }

        if (Choice != 10) {
            cout << "Returning to Movie Management menu." << endl;
            cout << "Press Enter to continue." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
        }

    } while (Choice != 10);
}
    
     void displayEmployeeManagement() {
        int Choice;
        do {
    	menu :
    	system ("cls");
    	cout << "\n\n\n\t\t\t\t\t\t=== Employee Management System ===" << endl;
        cout<<"\t\t\t\t\t\t********************************"<<endl;
        cout << "\t\t\t\t\t\t1. Register an employee" << endl;
        cout << "\t\t\t\t\t\t2. Display employee list" << endl;
        cout << "\t\t\t\t\t\t3. Modify a employee" << endl;
        cout << "\t\t\t\t\t\t4. Delete a employee" << endl;
        cout << "\t\t\t\t\t\t5. Restore a employee" << endl;
        cout << "\t\t\t\t\t\t6. Search a employee" << endl;
        cout << "\t\t\t\t\t\t7. Attendence of employee" << endl;
        cout << "\t\t\t\t\t\t8. Exit" << endl;
        cout<<"\t\t\t\t\t\t*********************************"<<endl;
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> Choice;
         cin.ignore();
		 if (Choice < 1 || Choice > 8 || cin.fail()) {
                cout << "\t\t\t\t\t\tPlease enter a valid choice." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else
			 {

        switch (Choice) {
          case 1:
          	system ("cls");
                empManager.registerEmployee();
                cin.get();
                break;
            case 2:
            	system ("cls");
                empManager.displayEmployeeList();
                cin.get();
                break;
                
                
case 3:
    {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter employee name to modify: ";
        string empName;
        getline(cin, empName);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        empManager.modifyEmployee(empName);
        cin.get();
        break;
    }
case 4:
	{
	
    system("cls");
    cout << "Enter employee name to delete: ";
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    
    string empNameToDelete;
    getline(cin, empNameToDelete);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    empManager.deleteEmployee(empNameToDelete);
    goto menu;
    
    break;

}

{

		    case 5:
		    system("cls");
		    cout << "Enter employee name to Restore: ";
		    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		    string empName;
		    getline(cin, empName);
		    empManager.restoreEmployee(empName);
		    cin.get();
		    break;

}
{

case 6: // Add a new case for searching employees
    system("cls");
    cout << "Enter employee name to search: ";
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
     string searchName;
    getline(cin, searchName);
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    empManager.searchEmployeeByName(searchName);
    cin.get();
    break;
}
{
					case 7:
						attend:
				   system("cls");
				    int Choice;
                cout << "\n\n\n\t\t\t\t\t\t\tAttendence Menu Employee" <<endl;
                cout<<"\t\t\t\t\t\t********************************"<<endl;
                cout << "\t\t\t\t\t\t1. Mark Attendence" << endl;
                cout << "\t\t\t\t\t\t2. Search Attendence" << endl;
                cout << "\t\t\t\t\t\t3. Display Attendence" << endl;
                cout << "\t\t\t\t\t\t4. Modify Attendence" << endl;
                cout << "\t\t\t\t\t\t5. Save Attendence" << endl;
                cout<<  "\t\t\t\t\t\t6. Exit Attendence Menu  "<<endl;
                cout << "\t\t\t\t\t\tEnter your choice: ";
                cin >> Choice;
                	cin.ignore();
			 switch(Choice){
			case 1:
				{
				
				system("cls");
         string employeeName;

empManager.markAttendanceByName(employeeName);
    cin.get();
    goto attend;
    break;
}
    case 2:
    	{
		 string empName;
    	system("cls");
    	cout << "Enter employee name: ";
getline(cin, empName);
    	empManager.displayIndividualAttendance( empName);
  
    	 cin.get();
		 goto attend;  
		 break;
	}
    	 case 3:
    	 	system("cls");
    empManager.displayAttendance();
    	
    	 cin.get();  
    	 goto attend;
		 break;
		 case 4:
		 	{
			 
		 	string employeeName;
			char newAttendanceStatus;
			system("cls");
			cout << "Enter employee name: ";
			cin >> employeeName;
			
			cout << "Enter new attendance status (P for present, A for absent, L for leave): ";
			cin >> newAttendanceStatus;
			cin.get(); 
			empManager.modifyAttendance(employeeName, toupper(newAttendanceStatus));
			cin.get(); 
			goto attend;
		 break;
	}
		  case 5: // New case to save attendance to a file
                empManager.saveAttendanceToFile();
                goto attend;
                break;
            case 6: // Exit option
                cout << "Exiting Attendance." << endl;
                
                break;
		 
	}
}

{

                 case 8:
            	system("cls");
                cout << "Exiting Employee Management menu." << endl;
                 cin.get();
                break;
}
        
            default:
                cout << "\t\t\t\t\t\tInvalid choice. Please try again." << endl;
                break;
    }
        if (Choice != 8) {
            std::cout << "Returning to Employee Management menu." << std::endl;
            std::cout << "Press Enter to continue." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
        }
		}
    } while (Choice != 8);

    }
    void displayCustomerReservationSystem()
    {
    	int choice;
    	  do {
        system("cls");
        cout << "\n\n\n\t\t\t\t\t\t=== Customer Reservation System ===" << endl;
        cout<<"\t\t\t\t\t\t********************************"<<endl;
        cout << "\t\t\t\t\t\t1. Display Customer List" << endl;
        cout << "\t\t\t\t\t\t2. Register a Customer" << endl;
        cout << "\t\t\t\t\t\t3. Search for a Customer" << endl;
        cout << "\t\t\t\t\t\t4. Delete a Customer" << endl;
        cout << "\t\t\t\t\t\t5. Cancel a Customer" << endl;
        cout << "\t\t\t\t\t\t6. Exit" << endl;
        cout<<"\t\t\t\t\t\t*********************************"<<endl;
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer
         	 if (choice < 1 || choice > 6 || cin.fail()) {
                cout << "\t\t\t\t\t\tPlease enter a valid choice." << endl;
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
                reservation.cancelReservation();
                cin.get();
                break;

            case 6:
                system("cls");
                cout << "Exiting Customer Menu." << endl;
                cin.get();
                break;

            default:
                cout << "\t\t\t\t\t\tInvalid choice. Please try again." << endl;
                break;
        }
    }
    } while (choice != 6);
	}
	
void displayTicketManagement() {
    int choice;
    TicketGenerator ticketGen; // Move this outside the loop

    do {
        system("cls");
        cout << "\n\n\n\t\t\t\t\t\t=== Customer Ticket System ===" << endl;
        cout << "\t\t\t\t\t\t********************************" << endl;
        cout << "\t\t\t\t\t\t1. Generate Ticket" << endl;
        cout << "\t\t\t\t\t\t2. Display Ticket" << endl;
        cout << "\t\t\t\t\t\t3. Delete Customer Tickets" << endl;
        cout << "\t\t\t\t\t\t4. Exit" << endl;
        cout << "\t\t\t\t\t\t*********************************" << endl;
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        if (choice < 1 || choice > 4 || cin.fail()) {
            cout << "\t\t\t\t\t\tPlease enter a valid choice." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
               system("cls");
                ticketGen.generateTicket();
                cin.get();
                break;
            }
            case 2:
                system("cls");
                ticketGen.displayAllTickets();
                cin.get();
                break;
            case 3: {
                system("cls");
                int ticketId;
                cout << "Enter Ticket ID to delete: ";
                cin >> ticketId;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ticketGen.deleteTicket(ticketId);
                cin.get();
                break;
            }
            case 4:
                system("cls");
                cout << "Exiting ticket Menu." << endl;
                cin.get();
                break;
            default:
                cout << "\t\t\t\t\t\tInvalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);
}
};


