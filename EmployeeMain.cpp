#include <iostream>
#include "EmployeeManager.h"


int main() {
    EmployeeManager empManager;
    
    int Choice;

    do {
    	menu :
    	system ("cls");
    	cout << "=== Employee Management System ===" << endl;
        cout << "1. Register an employee" << endl;
        cout << "2. Display employee list" << endl;
        cout << "3. Modify a employee" << endl;
        cout << "4. Delete a employee" << endl;
        cout << "5. Restore a employee" << endl;
        cout << "6. Search a employee" << endl;
        cout << "7. Attendence of employee" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> Choice;
         cin.ignore();
		 if (Choice < 1 || Choice > 8 || cin.fail()) {
                cout << "Please enter a valid choice." << endl;
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
                cout << "Attendence Menu Employee" <<endl;
                cout << "1. Mark Attendence" << endl;
                cout << "2. Search Attendence" << endl;
                cout << "3. Display Attendence" << endl;
                cout << "4. Modify Attendence" << endl;
                cout << "5. Save Attendence" << endl;
                cout<<  "6. Exit Attendence Menu  "<<endl;
                cout << "Enter your choice: ";
                cin >> Choice;
                	cin.ignore();
			 switch(Choice){
			case 1:
				{
				
				system("cls");
         string employeeName;
/*cout << "Enter employee name: ";
getline(cin, employeeName);
*/
// Call the function to mark attendance by name
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
                cout << "Exiting program." << endl;
                 cin.get();
                break;
}
         

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
    }
		}
    } while (Choice != 8);

    return 0;
}
