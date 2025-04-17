#include <iostream>
#include "MovieManager.h"

int main()
 {
    MovieManager movieManager;
    string searchName;
    int Choice;
    string movieName;

    do {
    	system ("cls");
        cout << "=== Movie Management System ===" << endl;
        cout << "1. Display Movie List" <<endl;
        cout << "2. Register a Movie" <<endl;
        cout << "3. Modify a Movie" << endl;
        cout << "4. Delete a Movie" << endl;
        cout << "5. Restore a Movie" << endl;
        cout << "6. Sort Movies" << endl;
        cout << "7. Search Movies" << endl;
        cout << "8. Display Movies Slot" << endl;
        cout << "9. Exit" << endl;           
      
                 
        cout << "Enter your choice: ";
        cin >> Choice;
		cin.ignore();
		 if (Choice < 1 || Choice > 8 || cin.fail()) {
                cout << "Please enter a valid choice." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else {
        switch (Choice)
		 {
            case 1:
            	system ("cls");
                movieManager.displayMovieList();
                  cin.get();
                break;

            case 2:
                system ("cls");
                movieManager.registerMovie();
                 cin.get();
                break;

            case 3:
            	{
				
            	system ("cls");
               cout << "Enter movie name to modify: ";
               	string movieName;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, movieName);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                movieManager.modifyMovie(movieName);
              
                 cin.get();
                 
                break;
}
            case 4:
            	system ("cls");
                cout << "Enter movie name to delete: ";
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                
                getline(cin, movieName);
                movieManager.deleteMovie(movieName);
                 cin.get();
                break;
                
                case 5:
                	system ("cls");
                cout << "Enter movie name to Restore: ";
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                getline(cin, movieName);
                movieManager.restoreMovie(movieName);
                 cin.get();
                break;

            case 6:
            	system ("cls");
                int sortChoice;
                cout << "Sort movies by: " <<endl;
                cout << "1. Name" << endl;
                cout << "2. Genre" << endl;
                cout << "3. Price" << endl;
                cout << "Enter your choice: ";
                cin >> sortChoice;
                	cin.ignore();
			 if (Choice < 1 || Choice > 3 || cin.fail()) {
               movieManager.sortMoviesBy(sortChoice);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            	} else{
				  cout << "Please enter a valid choice." << endl;
                cin.clear();
                 cin.get();
             
                break;
                }

                case 7: // Add a new case for search functionality
                system("cls");
                cout << "Enter movie name to search: ";
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
              
                getline(cin, searchName);
                movieManager.searchMovieByName(searchName);
                cin.get();
                break;
                case 8:
                system ("cls");	
                movieManager.displayMovieListWithSlots();
                 cin.get();
                 break;
                case 9:
            	system ("cls");
                cout << "Exiting program." << endl;
                cin.get();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        
		}
	}
    } 
	while (Choice != 9);
    return 0;
}

