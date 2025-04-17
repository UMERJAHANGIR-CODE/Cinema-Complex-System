#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <limits>
using namespace std;

class Employee {
public:
    string ID;
    string name;
    string department;
    string position;
    string shift;
      struct Date {
        int day;
        int month;
        int year;
    } 
	joinDate,
	 exitDate;
    double salary;
    char attendanceStatus;
    string registeredName;
    string registeredID;
  time_t registerTime;
   time_t modifiedTime;
    time_t deletedTime;
   time_t restoredTime;
  time_t attendenceTime;
   mutable map<char, int> individualCounts; // Map to store individual counts for each status


    Employee() : ID(""), name(""), department(""), position(""), salary(0.0), shift(""),registerTime(0), modifiedTime(0),deletedTime(0),
	restoredTime(0), attendenceTime(0), attendanceStatus('N')
	     {
		   individualCounts['P'] = 0;
        individualCounts['A'] = 0;
        individualCounts['L'] = 0;
		};
	   
      void updateAttendanceStatus(char status) {
        attendanceStatus = status;
        attendenceTime = time(0);
        individualCounts[status]++;
    }

    // Getter method to retrieve the attendance status
    char getAttendanceStatus() const {
        return attendanceStatus;
    }
};

class EmployeeManager {
private:
    vector<Employee> employeeList;
    vector<Employee> deletedEmployees;

public:
	void displayEmployeeList() {
		int totalEmployees = employeeList.size(); // Total number of employees
    if (employeeList.empty()) {
        cout << "No employees available." << endl;
    } else {
        cout << "#################################################################################" << endl;
 cout << '|' << setw(10) << "ID" << '|'
             << setw(10) << "Name" << '|'
             << setw(10) << "Department" << '|'
             << setw(6) << "Salary" << '|'
             << setw(10) << "Join Date" << '|'
             << setw(10) << "Left Date" << '|'
             << setw(6) << "Duty Shift" << '|'
			 << setw(10) << "Attendance" << '|' << endl;
        cout << "#################################################################################" << endl;
      

        for (const auto& employee : employeeList) {
            cout << '|' << setw(10) << employee.ID << '|'
                 << setw(10) << employee.name << '|'
                 << setw(10) << employee.department << '|'
                 << setw(6) << employee.salary << '|'
                 << setw(10) << employee.joinDate.day << " D " << '/'
                 << setw(2) << employee.joinDate.month << " M " << '/'
                 << setw(4) << employee.joinDate.year << " Y " << '|'
                 << setw(10) << employee.exitDate.day<<" D " << '/'
                 << setw(2) << employee.exitDate.month<<" M " << '/'
                 << setw(4) << employee.exitDate.year <<" Y " << '|'
                 << setw(6) << employee.shift << '|'
			     << setw(10) << employee.attendanceStatus << '|'<< endl;
            cout << "Employee was registered at: " << ctime(&employee.registerTime); // Display hire time
            if (employee.modifiedTime != 0) {
                cout << "Employee was modified at: " << ctime(&employee.modifiedTime) << endl;
            } else {
                cout << "Employee is not modified yet." << endl;
            }
            cout << "#####################################################################" << endl;
        
        }
        cout << "Total Employees: " << totalEmployees << endl;
    }
}
void registerEmployee() {
    char registerAnother;
    do {
        Employee newEmployee;
        newEmployee.registeredName = newEmployee.name;  // Set the registered name
        cout << "Employee register time: ";
        time_t t = time(0);
        cout << ctime(&t) << endl;
        cout << "Enter Employee ID: ";
        do {
            if (getline(cin, newEmployee.ID)) {
                if (newEmployee.ID.empty()) {
                    cout << "Please enter an ID for the employee." << endl;
                } else {
                    break;
                }
            }
        } while (newEmployee.ID.empty());

        newEmployee.registeredID = newEmployee.ID;

        cout << "Enter employee name: ";
        do {
            if (getline(cin, newEmployee.name)) {
                if (newEmployee.name.empty()) {
                    cout << "Please enter a name for the employee." << endl;
                } else {
                    break;
                }
            }
        } while (newEmployee.name.empty());

        auto it = find_if(employeeList.begin(), employeeList.end(),
                          [&newEmployee](const Employee& employee) { return employee.name == newEmployee.name; });

        if (it != employeeList.end()) {
            cout << "An employee with the name " << newEmployee.name << " is already registered." << endl;
            string choice;
            cout << "Do you want to change the employee name? (Y/N): ";
            cin >> choice;
            if (choice == "Y" || choice == "y") {
                cout << "Enter the new employee name: ";
                cin.ignore();
                getline(cin, newEmployee.name);
            } else {
                return; // Abort the registration process
            }
        }

        newEmployee.registeredName = newEmployee.name;  // Set the registered name
        
        cout << "Enter employee department: ";
        do{
		
        if(getline(cin, newEmployee.department)){
                if (newEmployee.department.empty()) {
                    cout << "Please enter a department for the employee." << endl;
                } else {
                    break;
                }
            }
        } while (newEmployee.department.empty());
        
        cout << "Enter employee duty Shift: ";
        cin.ignore();
        getline(cin, newEmployee.shift);

          do {
            cout << "Enter employee salary: ";
            if (!(cin >> newEmployee.salary)) {
                cout << "Please enter a valid salary." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break; // Valid input, exit loop
            }
        } while (true);
        string choice;
          int day, month, year;
     do {
        cout << "Do you want to enter the join Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	    newEmployee.joinDate.day = 0;
                newEmployee.joinDate.month = 0;
                newEmployee.joinDate.year = 0;
            break;
        } else if (choice == "Y" || choice == "y") {
            cout << "Enter Employee join date (DD MM YYYY): ";
            cin >> day >> month >> year;

            if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
                cout << "Invalid date entered. Please enter again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                newEmployee.joinDate.day = day;
                newEmployee.joinDate.month = month;
                newEmployee.joinDate.year = year;
                break;
            }
        } else {
            cout << "Invalid choice. Please enter Y or N." << endl;
        }
    } while (true);
      
  do {
      cout << "Do you want to enter Exit or Left Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	 newEmployee.exitDate.day = 0;
             newEmployee.exitDate.month = 0;
              newEmployee.exitDate.year = 0;
            break;
        }
        cout << "Enter the date this Employee left out or Exit the cinema (DD MM YYYY): ";
        cin >> day >> month >> year;

        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100) {
             newEmployee.exitDate.day = day;
             newEmployee.exitDate.month = month;
              newEmployee.exitDate.year = year;
        break; // Valid date, exit loop
        } else {
            cout << "Invalid date entered. Please enter again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
        
        newEmployee.registerTime = time(0); // Record the hiring time when the employee is registered
        employeeList.push_back(newEmployee);

         ofstream outputFile("C:/Users/Hassan/Desktop/Registered_Employee's.txt", ios::app); // Open in append mode

    if (outputFile.is_open()) {
        // Write the movie details to the file
        outputFile << "Employee ID: " << newEmployee.ID  << endl;
        outputFile << "Employee Name: "  << newEmployee.name << endl;
        outputFile << "Employee Department: " << newEmployee.department << endl;
        outputFile << "Employee Salary: " << newEmployee.salary << endl;
        outputFile << "Employee join Date: " << newEmployee.joinDate.day << "/" << newEmployee.joinDate.month << "/" << newEmployee.joinDate.year << endl;
        outputFile << "Employee left Out Date: " << newEmployee.exitDate.day << "/" << newEmployee.exitDate.month << "/" << newEmployee.exitDate.year << endl;
       
   
        outputFile << "Registered Time: " << ctime(&newEmployee.registerTime) << endl;
        outputFile << "-----------------------------" << endl;

        // Close the file
        outputFile.close();

        cout << "Employee details saved successfully!" << endl;
        cin.get();
        cin.get();
        } else {
        cout << "Unable to open the file!" << endl;
    }
    system("cls");

        cout << "Do you want to register another employee? (Y/N): ";
        cin >> registerAnother;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (registerAnother == 'N' || registerAnother == 'n') {
            break; // Exit the loop if the user doesn't want to register another employee
        }
    } while (true);
     // Moving this function call outside the loop for proper sequence
}
    
    void modifyEmployee(const string& empName) {
    bool found = false;

    // Opening file to save modified employee details
    ofstream outputFile("C:/Users/Hassan/Desktop/Modified_Employees.txt", ios::app);

    if (employeeList.empty()) {
        cout << "No employees are registered yet." << endl;
        return;
    }

    string lowerInput = empName;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    for (auto& employee : employeeList) {
        string lowerEmployeeName = employee.name;
        transform(lowerEmployeeName.begin(), lowerEmployeeName.end(), lowerEmployeeName.begin(), ::tolower);

        if (lowerEmployeeName == lowerInput) {
            found = true;

            do {
                cout << "Enter new details for employee: " << employee.name << endl;
                time_t t = time(0);
                cout << "Employee modified at time: " << ctime(&t) << endl;
                cout << "What do you want to modify?" << endl;
                cout << "1. Employee ID" << endl;
                cout << "2. Employee Name" << endl;
                cout << "3. Employee Department" << endl;
	            cout << "4. Employee Salary" << endl;
	            cout << "5. Employee Join Date" << endl;
	            cout << "6. Employee Left Date" << endl;
	            cout << "7. Employee Shift Duty" << endl;
	            cout << "8. Return to main menu" << endl;
                int choice;
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
    case 1:
        cout << "Employee ID is: " << employee.ID << endl;
        cout << "Enter a new ID for Employee: ";
        getline(cin, employee.ID);
        cout << "\nEmployee ID updated successfully." << endl;
        break;

    case 2:
        cout << "Employee Name is: " << employee.name << endl;
        cout << "Enter a new Name for Employee: ";
        getline(cin, employee.name);
        cout << "\nEmployee Name updated successfully." << endl;
        break;

    case 3:
        cout << "Employee Department is: " << employee.department << endl;
        cout << "Enter a new Department for Employee: ";
        getline(cin, employee.department);
        cout << "\nEmployee Department updated successfully." << endl;
        break;

    case 4:
        cout << "Employee Shift is: " << employee.shift << endl;
        cout << "Enter a new Shift for Employee: ";
        getline(cin, employee.shift);
        cout << "\nEmployee Shift updated successfully." << endl;
        break;

    case 5:
        cout << "Employee Salary is: " << employee.salary << endl;
        cout << "Enter a new Salary for Employee: ";
        cin >> employee.salary;
        cout << "\nEmployee Salary updated successfully." << endl;
        break;

    case 6:
        int day, month, year;
        cout << "Employee Join Date is: " << employee.joinDate.day << " D " << employee.joinDate.month << " M " << employee.joinDate.year << " Y" << endl << endl;
        do {
            cout << "Enter a new Join date for Employee (DD MM YYYY): ";
            cin >> day >> month >> year;
            // Check for valid input
            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100) {
                employee.joinDate.day = day;
                employee.joinDate.month = month;
                employee.joinDate.year = year;
                cout << "\nEmployee Join date updated successfully." << endl;
                break; // Exit loop after setting the date
            } else {
                cout << "Invalid date entered. Please enter again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (true);
        break;

    case 7:
        cout << "Employee Exit Date is: " << employee.exitDate.day << " D " << employee.exitDate.month << " M " << employee.exitDate.year << " Y" << endl << endl;
        do {
            cout << "Enter a new Exit date for Employee (DD MM YYYY): ";
            cin >> day >> month >> year;
            // Check for valid input
            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100) {
                employee.exitDate.day = day;
                employee.exitDate.month = month;
                employee.exitDate.year = year;
                cout << "\nEmployee Exit date updated successfully." << endl;
                break; // Exit loop after setting the date
            } else {
                cout << "Invalid date entered. Please enter again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (true);
        break;

    case 8:
        cout << "Returning to main menu." << endl;
        break;

    default:
        cout << "Invalid choice." << endl;
        break;
}

// Update modification time
employee.modifiedTime = time(0);


                if (outputFile.is_open()) {
                    // Write employee details to the file
                    

                    outputFile << "Registered Employee Name Which Modified is: " << employee.registeredName << endl;
                    outputFile << "Registered Employee ID Which Modified is: " << employee.registeredID << endl;
                    outputFile << "Employee ID: " << employee.ID << endl;
					outputFile << "Employee Name: " << employee.name << endl;
					outputFile << "Employee Department: " << employee.department << endl;
					outputFile << "Employee Shift: " << employee.shift << endl;
					outputFile << "Employee Salary: " << employee.salary << endl;
					outputFile << "Employee Join Date: " << employee.joinDate.day << "/" << employee.joinDate.month << "/" << employee.joinDate.year << endl;
					outputFile << "Employee Exit Date: " << employee.exitDate.day << "/" << employee.exitDate.month << "/" << employee.exitDate.year << endl;
					outputFile << "Modified Time: " << ctime(&employee.modifiedTime) << endl;
					outputFile << "-----------------------------" << endl;


                    cout << "Employee details saved to file successfully!" << endl;
                } else {
                    cout << "Unable to open the file!" << endl;
                }

                // Ask if the user wants to modify another employee
                char modifyAgain;
                cout << "Do you want to modify another employee? (y/n): ";
                cin >> modifyAgain;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (tolower(modifyAgain) != 'y') {
                    // Close the file
                    outputFile.close();
                    return; // Exit the function
                }
            } while (true);
        }
    }

    if (!found) {
    cout << "Employee not found." << endl;
    char searchAgain;
    cout << "Do you want to search for another employee to modify? (y/n): ";
    cin >> searchAgain;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(searchAgain) == 'n') {
        // Close the file
        outputFile.close();
        return; // Exit the function
    } else {
        // Ask for another employee name and continue the loop
        cout << "Enter the name of the employee you want to modify: ";
        string newEmployeeName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newEmployeeName);
        modifyEmployee(newEmployeeName); // Recursive call to search for the new employee
    }
}

}

void deleteEmployee(string& empName) {
    while (true) {
        auto it = find_if(employeeList.begin(), employeeList.end(),
                          [&empName](const Employee& emp) { return emp.name == empName; });

        if (it != employeeList.end()) {
            time_t currentTime = time(0);
            it->deletedTime = currentTime;
            deletedEmployees.push_back(*it);
            employeeList.erase(it);

            cout << "Employee '" << empName << "' deleted successfully." << endl;
            cout << "Deleted Time: " << ctime(&currentTime) << endl;

            ofstream outputFile("C:/Users/Hassan/Desktop/Deleted_employees.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << "Employee Name: " << empName << endl;
                outputFile << "Deleted Time: " << ctime(&currentTime) << endl;
                outputFile << "-----------------------------" << endl;
                outputFile.close();

                cout << "Employee details deleted from file successfully!" << endl;
            } else {
                cout << "Unable to open the file!" << endl;
            }

            char retryChoice;
            cout << "Do you want to delete another employee? (Y/N): ";
            cin >> retryChoice;
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');

            if (retryChoice == 'N' || retryChoice == 'n') {
                return; // Exit the loop if the user doesn't want to delete another employee
            } else {
                cout << "Enter Employee Name to delete: ";
                getline(cin, empName);
            }
        } else {
            cout << "Employee '" << empName << "' not found in the employee list." << endl;
            char retryChoice;
            cout << "Do you want to delete another employee? (Y/N): ";
            cin >> retryChoice;
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            
            if (retryChoice == 'N' || retryChoice == 'n') {
                break;// Exit the loop if the user doesn't want to delete another employee
            } else {
                cout << "Enter Employee Name to delete: ";
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                getline(cin, empName);
            }
        }
    }
}

void restoreEmployee(string& empName) {
    while (true) {
        auto it = find_if(deletedEmployees.begin(), deletedEmployees.end(),
                          [&empName](const Employee& emp) { return emp.name == empName; });

        if (it != deletedEmployees.end()) {
            time_t currentTime = time(0);
            it->restoredTime = currentTime;
            employeeList.push_back(*it);
            deletedEmployees.erase(it);
            cout << "Employee '" << empName << "' restored successfully." << endl;
            cout << "Restored Time: " << ctime(&currentTime) << endl;

            ofstream outputFile("C:/Users/Hassan/Desktop/Restored_employees.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << "Employee Name: " << empName << endl;
                outputFile << "Restored Time: " << ctime(&currentTime) << endl;
                outputFile << "-----------------------------" << endl;
                outputFile.close();

                cout << "Employee details restored to file successfully!" << endl;
                cin.get();
            } else {
                cout << "Unable to open the file!" << endl;
            }
        } else {
            cout << "Employee '" << empName << "' not found in deleted list." << endl;
            char retryChoice;
            cout << "Do you want to restore another employee? (Y/N): ";
            cin >> retryChoice;

            if (retryChoice == 'N' || retryChoice == 'n') {
                break; // Exit the loop if the user doesn't want to restore another employee
            } else {
                cout << "Enter Employee Name to Restore: ";
                cin.ignore(); // Clear input buffer
                getline(cin, empName);
            }
        }
    }
}
void searchEmployeeByName(string& empName) {
    while (true) {
        bool found = false;
    
     

        for (const auto& employee : employeeList) {
            if (employee.name == empName) {
                found = true;
                // Display employee details
                cout << "Employee found:" << endl;
                cout << "Employee Name: " << employee.name << endl;
                cout << "Employee ID: " << employee.ID << endl;
                cout << "Department: " << employee.department << endl;
                cout << "Position: " << employee.position << endl;
                cout << "Salary: " << employee.salary << endl;
                cout << "Join Date: " << employee.joinDate.day << "/" << employee.joinDate.month << "/" << employee.joinDate.year << endl;
                cout << "Duty Shift: " << employee.shift << endl;
                cout << "Employee Attendance Status: " << employee.attendanceStatus << '|' << endl;
                cout << "Total Presents: " << employee.individualCounts['P'] << endl;
                cout << "Total Absents: " << employee.individualCounts['A'] << endl;
                cout << "Total Leaves: " << employee.individualCounts['L'] << endl;

                int totalAttendance = employee.individualCounts['P'] + employee.individualCounts['A'] + employee.individualCounts['L'];
                cout << "Total Employee Attendance: " << totalAttendance << endl;


                cout << "Employee was registered at: " << ctime(&employee.registerTime);
                if (employee.modifiedTime != 0) {
                    cout << "Modified Time: " << ctime(&employee.modifiedTime) << endl;
                } else {
                    cout << "Employee has not been modified yet." << endl;
                }
                cout << "-----------------------------" << endl;
            }
        }

        if (!found) {
    
            cout << "Employee not found." << endl;
            cin.get();
        }

        cout << "Do you want to search for another employee? (Y/N): ";
        char searchAgain;
        cin >> searchAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (searchAgain == 'N' || searchAgain == 'n') {
            break; // Exit the outer loop if the user doesn't want to search again
        } else {
            cout << "Enter Employee Name to search: ";
            getline(cin, empName);
        }
    }
}
   void markAttendanceByName( string& empName) {
   	do{
   		empName.clear(); // Clear previous employee's name before prompting for a new one
        
        cout << "Enter employee name: ";
        cin >> empName;
	
    cout << "Employee Attendance time: ";
    time_t t = time(0);
    cout << ctime(&t) << endl;
    auto it = find_if(employeeList.begin(), employeeList.end(), [&](const Employee& emp) {
        return emp.name == empName;
    });

    if (it != employeeList.end()) {
        char attendanceChoice;
        cout << "Mark attendance (P for present, A for absent, L for leave) for " << empName << ": ";
        cin >> attendanceChoice;

        switch (toupper(attendanceChoice)) {
            case 'P':
                it->updateAttendanceStatus('P');
                cout << empName << "'s attendance marked as present." << endl;
                cin.get();
                break;
            case 'A':
                it->updateAttendanceStatus('A');
                cout << empName << "'s attendance marked as absent." << endl;
                cin.get();
                break;
            case 'L':
                it->updateAttendanceStatus('L');
                cout << empName << "'s attendance marked as on leave." << endl;
                cin.get();
                break;
            default:
                cout << "Invalid choice. Attendance not marked." << endl;
                cin.get();
                break;
        }
    } else {
        cout << "Employee not found." << endl;
    }
    
      cout << "Do you want to mark attendance for another employee? (Y/N): ";
        char markAgain;
        cin >> markAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (markAgain == 'N' || markAgain == 'n') {
            break; // Exit the loop if the user doesn't want to mark attendance for another employee
        }
    } while (true);
}

void displayIndividualAttendance(const string& empName) {
    auto it = find_if(employeeList.begin(), employeeList.end(), [&](const Employee& emp) {
        return emp.name == empName;
    });

    if (it != employeeList.end()) {
        cout << "Employee Name: " << it->name << "\tAttendance: " << it->attendanceStatus << endl;
        cout << "Total Presents: " << it->individualCounts['P'] << endl;
        cout << "Total Absents: " << it->individualCounts['A'] << endl;
        cout << "Total Leaves: " << it->individualCounts['L'] << endl;
        int totalAttendance = it->individualCounts['P'] + it->individualCounts['A'] + it->individualCounts['L'];
            cout << "Total Employee Attendance: " << totalAttendance << endl;
    } else {
        cout << "Employee not found." << endl;
    }
}

void displayAttendance() {
    cout << "=== Display Attendance ===" << endl;
    for (const auto& employee : employeeList) {
        cout << "Employee Name: " << employee.name << "\tAttendance: " << employee.attendanceStatus << endl;
        
    }
}

  void modifyAttendance( string& empName, char newStatus) {
  	do {
    auto it = find_if(employeeList.begin(), employeeList.end(), [&](const Employee& emp) {
        return emp.name == empName;
    });

    if (it != employeeList.end()) {
        cout << "Employee found: " << empName << endl;
        cout << "Old Attendance Status: " << it->attendanceStatus << endl;
        char newStatus;
            cout << "Enter new Attendance Status (P for present, A for absent, L for leave): ";
            cin >> newStatus;
            newStatus = toupper(newStatus); // Convert to uppercase

            switch (newStatus) {
                case 'P':
                    it->updateAttendanceStatus('P');
                    cout << "Attendance status updated to: Present" << endl;
                    cin.get();
                    break;
                case 'A':
                    it->updateAttendanceStatus('A');
                    cout << "Attendance status updated to: Absent" << endl;
                    cin.get();
                    break;
                case 'L':
                    it->updateAttendanceStatus('L');
                    cout << "Attendance status updated to: On leave" << endl;
                    cin.get();
                    break;
                default:
                    cout << "Invalid choice. Attendance status not updated." << endl;
                    cin.get();
                    break;
            }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    } else {
        cout << "Employee not found." << endl;
    }
    cout << "Do you want to modify attendance for another employee? (Y/N): ";
        char modifyAgain;
        cin >> modifyAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (modifyAgain == 'N' || modifyAgain == 'n') {
            break; // Exit the loop if the user doesn't want to modify attendance for another employee
        }

        cout << "Enter employee name: ";
        cin >> empName;

    } while (true);
}
void saveAttendanceToFile() {
    ofstream outFile("attendance.txt", ios::app);
    if (outFile.is_open()) {
        for (const auto& employee : employeeList) {
            outFile << "Employee Name: " << employee.name << "\tAttendance: " << employee.attendanceStatus << endl;
            outFile << "Attendence Time: " << ctime(&employee.attendenceTime);
            
        }
        outFile.close();
        cout << "Attendance data saved to file 'attendance.txt'." << endl;
        cin.get();
    } else {
        cout << "Unable to open file for saving attendance." << endl;
        cin.get();
    }
}
  

};
#endif
