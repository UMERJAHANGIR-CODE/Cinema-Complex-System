#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H



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
using namespace std;
class Movie
 {
public:

    string ID; 
    string name;
    string registeredName;
    string registeredID;
    string genre;
    double price;
    struct Date {
        int day;
        int month;
        int year;
    } 
	entryDate,
	 exitDate;

    int ratingPg;
   time_t registerTime;
   time_t modifiedTime;   // Store modification time
   time_t deletedTime;
   time_t restoredTime;
   int slotNumber;
	// Default constructor
    Movie() :  ID(""), name(""), genre(""), price(0.0), ratingPg{0}, registerTime(0), modifiedTime(0),deletedTime(0),restoredTime(0) {}
};
 
	 // Define the MovieSlot structure
struct MovieSlot {
    string movieName;
   int slotNumber;
};
class MovieManager {
private:
    vector<Movie> movieList;
    vector<Movie> deletedMovies;
    vector<MovieSlot> movieSlots;

public:

void displayMovieList() {
    // Assuming movieList and movieSlots are global variables or accessible within this scope

    // Open an ofstream for writing to a file
    std::ofstream outFile("movie_list_output.txt");

    int totalMovies = movieList.size();

    if (movieList.empty()) {
        outFile << "No movies available." << std::endl;
    } else {
        outFile << "################################################################################################################################" << std::endl;
        outFile << '|' << std::setw(8) << "Movie ID" << '|'
            << std::setw(15) << "Name" << '|'
            << std::setw(15) << "Genre" << '|'
            << std::setw(10) << "Price" << '|'
            << std::setw(15) << "Rel. Date" << '|'
            << std::setw(15) << "Exp. Date" << '|'
            << std::setw(8) << "Rating" << '|'
            << std::setw(8) << "Slot" << '|' << std::endl;
        outFile << "#################################################################################################################################" << std::endl;

        for (size_t i = 0; i < movieList.size(); ++i) {
            outFile << '|' << std::setw(8) << movieList[i].ID << '|'
                << std::setw(15) << movieList[i].name << '|'
                << std::setw(15) << movieList[i].genre << '|'
                << std::setw(10) << movieList[i].price << '|'
                << std::setw(15) << movieList[i].entryDate.day << " D / "
                << std::setw(2) << movieList[i].entryDate.month << " M / "
                << std::setw(4) << movieList[i].entryDate.year << " Y" << '|'
                << std::setw(15) << movieList[i].exitDate.day << " D / "
                << std::setw(2) << movieList[i].exitDate.month << " M / "
                << std::setw(4) << movieList[i].exitDate.year << " Y" << '|'
                << std::setw(8) << movieList[i].ratingPg << '|';

            // Check if the movie has a slot assigned
            if (i < movieSlots.size()) {
                outFile << std::setw(8) << movieSlots[i].slotNumber << '|';
            } else {
                outFile << std::setw(8) << "N/A" << '|'; // No slot assigned
            }

            outFile << std::endl;
            outFile << "Movie was registered at: " << std::ctime(&movieList[i].registerTime);

            if (movieList[i].modifiedTime != 0) {
                outFile << "Movie was modified at: " << std::ctime(&movieList[i].modifiedTime) << std::endl;
            } else {
                outFile << "Movie is not modified yet." << std::endl;
            }
        }
        outFile << "#################################################################################" << std::endl;
    }
    outFile << "Total Movies: " << totalMovies << std::endl;
    outFile.close(); // Close the ofstream after writing

    // To read from the file later, use ifstream
    std::ifstream inFile("movie_list_output.txt",ios::app|ios::binary);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;  // Print each line from the file
        }
        inFile.close(); // Close the ifstream when done reading
    } else {
        std::cerr << "Unable to open the file for reading." << std::endl;
    }
}
void viewAllMovies() {
    std::ifstream inFile("movie_list_output.txt");
    
    if (!inFile.is_open()) {
        std::cerr << "Unable to open the file for reading." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;  // Print each line from the file
    }

    inFile.close(); // Close the ifstream when done reading
}
void registerMovie() {
	char registerAnother;
	do
	{

    Movie newMovie;
    newMovie.registeredName = newMovie.name;  // Set the registered name
    cout << "Movie register time: ";
    time_t t = time(0);
    cout << ctime(&t) << endl;
    cout<<"Enter Movie ID: ";
    do{
  if(getline(cin,newMovie.ID)){
  	if(newMovie.ID.empty()){
  		cout << "Please write any ID of Movie" << endl;
	  }else {
                break;
            }
  }
  } while (newMovie.ID.empty());
  
  newMovie.registeredID=newMovie.ID;
  
    cout << "Enter movie name: ";
    do {
        if (getline(cin, newMovie.name)) {
            if (newMovie.name.empty()) {
                cout << "Please write any name" << endl;
            } else {
                break;
            }
        }
    } while (newMovie.name.empty());

    auto it = find_if(movieList.begin(), movieList.end(),
                      [&newMovie](const Movie& movie) { return movie.name == newMovie.name; });

    if (it != movieList.end()) {
        cout << "You have already registered a movie with the name: " << newMovie.name << endl;
        string choice;
        cout << "Do you want to change the movie name? (Y/N): ";
        cin >> choice;
        if (choice == "Y" || choice == "y") {
            cout << "Enter new movie name: ";
            cin.ignore();
            getline(cin, newMovie.name);
        } else {
            return; // Abort the registration process
        }
    }
    
  newMovie.registeredName = newMovie.name;  // Set the registered name
  
  while (true) {
            std::cout << "Enter slot number for the movie: ";
            std::string slotInput;
            std::getline(std::cin, slotInput);

            if (slotInput.empty()) {
                std::cout << "Please enter a slot number." << std::endl;
            } else if (std::all_of(slotInput.begin(), slotInput.end(), ::isdigit)) {
                newMovie.slotNumber = std::stoi(slotInput);
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid slot number." << std::endl;
            }
        }
  
    string choice;
    do {
        cout << "Do you want to proceed with the Genre (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
            break;
        }

        cout << "Enter movie genre (as a string): ";
        cin.ignore();
        if (getline(cin, newMovie.genre)) {
            if (newMovie.genre.empty()) {
                cout << "Please enter a non-empty genre." << endl;
            } else if (all_of(newMovie.genre.begin(), newMovie.genre.end(), [](char c) { return isalpha(c) || isspace(c); })) {
                break;
            } else {
                cout << "Please enter a genre containing only letters." << endl;
            }
        } else {
            cout << "Input failed." << endl;
            return;
        }
    } while (true);

    do {
    cout << "Enter movie price: ";
    if (!(cin >> newMovie.price)) {
        cout << "Please enter a valid price." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        break; // Valid input, exit loop
    }
} while (true);

    int day, month, year;
     do {
        cout << "Do you want to proceed with the Release Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	 newMovie.entryDate.day = 0;
                newMovie.entryDate.month = 0;
                newMovie.entryDate.year = 0;
            break;
        } else if (choice == "Y" || choice == "y") {
            cout << "Enter movie release date (DD MM YYYY): ";
            cin >> day >> month >> year;

            if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
                cout << "Invalid date entered. Please enter again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                newMovie.entryDate.day = day;
                newMovie.entryDate.month = month;
                newMovie.entryDate.year = year;
                break;
            }
        } else {
            cout << "Invalid choice. Please enter Y or N." << endl;
        }
    } while (true);
      
  do {
      cout << "Do you want to proceed with Goes Out Date (Y/N)? ";
        cin >> choice;
        if (choice == "N" || choice == "n") {
        	 newMovie.exitDate.day = 0;
             newMovie.exitDate.month = 0;
              newMovie.exitDate.year = 0;
            break;
        }
        cout << "Enter the date this movie goes out of cinema (DD MM YYYY): ";
        cin >> day >> month >> year;

        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100) {
             newMovie.exitDate.day = day;
             newMovie.exitDate.month = month;
              newMovie.exitDate.year = year;
        break; // Valid date, exit loop
        } else {
            cout << "Invalid date entered. Please enter again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
    do {
        cout << "Enter viewer rating out of 10: ";
        cin >> newMovie.ratingPg;

        if (cin.fail() || newMovie.ratingPg < 0 || newMovie.ratingPg > 10) {
            cout << "Please enter a valid rating between 0 and 10." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    newMovie.registerTime = time(0); // Record the registration time when the movie is registered
    movieList.push_back(newMovie);
     MovieSlot movieSlot;
        movieSlot.movieName = newMovie.name;
        movieSlot.slotNumber = newMovie.slotNumber; // Assuming MovieSlot has a slotNumber member

        // Add the slot to movieSlots
        movieSlots.push_back(movieSlot);
      ofstream outputFile("Registered_movies.txt", ios::app); // Open in append mode

    if (outputFile.is_open()) {
        // Write the movie details to the file
        outputFile << "Movie ID: " << newMovie.ID << endl;
        outputFile << "Movie Name: " << newMovie.name << endl;
        outputFile << "Genre: " << newMovie.genre << endl;
        outputFile << "Price: " << newMovie.price << endl;
        outputFile << "Release Date: " << newMovie.entryDate.day << "/" << newMovie.entryDate.month << "/" << newMovie.entryDate.year << endl;
        outputFile << "Goes Out Date: " << newMovie.exitDate.day << "/" << newMovie.exitDate.month << "/" << newMovie.exitDate.year << endl;
        outputFile << "Viewer Rating: " << newMovie.ratingPg << "/10" << endl;
        outputFile << "Registered Time: " << ctime(&newMovie.registerTime) << endl;
        outputFile << "-----------------------------" << endl;

        // Close the file
        outputFile.close();

        cout << "Movie details saved to file successfully!" << endl;
        cin.get();
        cin.get();
    } else {
        cout << "Unable to open the file!" << endl;
    }
    system("cls");
    cout << "Do you want to register another movie? (Y/N): ";
        cin >> registerAnother;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (registerAnother == 'N' || registerAnother == 'n') {
            break; // Exit the loop if the user doesn't want to register another movie
        }
}while(true);
}

void modifyMovie(const string& movieName) {
    bool found = false;

    ofstream outputFile("C:/Users/Hassan/Desktop/Modified_movies.txt", ios::app); // Open in append mode

    if (movieList.empty()) {
        cout << "No movies are registered yet." << endl;
        return;
    }

    string lowerInput = movieName;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    for (auto& movie : movieList) {
        string lowerMovieName = movie.name;
        transform(lowerMovieName.begin(), lowerMovieName.end(), lowerMovieName.begin(), ::tolower);

        if (lowerMovieName == lowerInput) {
            found = true;

            do {
                cout << "Enter new details for movie: " << movie.name << endl;
                time_t t = time(0);
                cout << "Movie modified at time: " << ctime(&t) << endl;

                cout << "What do you want to modify?" << endl;
                cout << "1. Movie ID" << endl;
                cout << "2. Name" << endl;
                cout << "3. Genre" << endl;
	            cout << "4. Price" << endl;
	            cout << "5. Release Date" << endl;
	            cout << "6. Expiry Date" << endl;
	            cout << "7. Rating (viewer reviews)" << endl;
	            cout << "8. Return to main menu" << endl;
                int choice;
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                    case 1:
                        cout << "Movie ID is: " << movie.ID << endl;
                        cout << "Enter a new ID for movie: ";
                        getline(cin, movie.ID);
                        cout << "\nMovie ID updated successfully." << endl;
                        break;

                    case 2:
                        cout << "Movie Name is: " << movie.name << endl;
                        cout << "Enter a new Name for movie: ";
                        getline(cin, movie.name);
                        cout << "\nMovie Name updated successfully." << endl;
                        break;
                          
                       
                    case 3:
                        system("cls");
                        cout << "Movie Genre is: " << movie.genre << endl << endl;
                        cout << "Enter a new Genre for movie: ";
                        getline(cin, movie.genre);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nMovie Genre updated successfully." << endl;
                        
                        break;
                    case 4:
                        system("cls");
                        cout << "Movie Price is: " << movie.price << endl << endl;
                        cout << "Enter a new Price for movie: ";
                        cin >> movie.price;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nMovie Price updated successfully." << endl;
                        break;
                    case 5:
                        system("cls");
                        cout << "Movie Release Date is: " << movie.entryDate.day << " D " << movie.entryDate.month << " M " << movie.entryDate.year << " Y" << endl << endl;

                        int day, month, year;

                        do {
                            cout << "Enter a new Release date for movie (DD MM YYYY): ";
                            cin >> day >> month >> year;

                            // Check for valid input
                            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100) {
                                movie.entryDate.day = day;
                                movie.entryDate.month = month;
                                movie.entryDate.year = year;
                                cout << "\nMovie Release date updated successfully." << endl;
                                break; // Exit loop after setting the date
                            } else {
                                cout << "Invalid date entered. Please enter again." << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (true);
                        break;
                    case 6:
                        system("cls");
                        cout << "Movie Goes Out Date is: " << movie.exitDate.day << " D " << movie.exitDate.month << " M " << movie.exitDate.year << " Y" << endl << endl;

                        do {
	                            cout << "Enter the new date for this movie Goes out of cinema (DD MM YYYY): ";
	                            cin >> day >> month >> year;
	
	                            // Check for valid input
	                            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900 && year <= 2100) {
	                                movie.exitDate.day = day;
	                                movie.exitDate.month = month;
	                                movie.exitDate.year = year;
	                                cout << "\nMovie Goes Out Date updated successfully." << endl;
	                                break;
	                            } else {
	                                cout << "Invalid date entered. Please enter again." << endl;
	                                cin.clear();
	                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
	                            }
	                        } while (true);
                        break;
                    case 7:
                        system("cls");
                        cout << "Movie Viewer Rating is: '" << movie.ratingPg << "' and PG rating is " << movie.ratingPg << endl << endl;
                        cout << "Enter a new viewer Rating out of 10: ";
                        cin >> movie.ratingPg;
                        cout << "\nEnter the new PG rating for movie: ";
                       

                        case 8:
                            cout << "Returning to main menu." << endl;
                            break;

                    default:
                        cout << "Invalid choice." << endl;
                        break;
                }

                // Update modification time
                movie.modifiedTime = time(0);

                // Write movie details to the file
                if (outputFile.is_open()) {
                  outputFile << "Registered Movie Name Which Modified is: " << movie.registeredName << endl;
			        outputFile << "Registered Movie ID Which Modified is: " << movie.registeredID << endl;
					outputFile << "Movie ID: " << movie.ID << endl; 
			        outputFile << "Movie Name: " << movie.name << endl;
			        outputFile << "Genre: " << movie.genre << endl;
			        outputFile << "Price: " << movie.price << endl;
			        outputFile << "Release Date: " << movie.entryDate.day << "/" << movie.entryDate.month << "/" << movie.entryDate.year << endl;
			        outputFile << "Goes Out Date: " << movie.exitDate.day << "/" << movie.exitDate.month << "/" << movie.exitDate.year << endl;
			        outputFile << "Viewer Rating: " << movie.ratingPg << "/10" << endl;
			        
			        outputFile << "Modified Time: " << ctime(&movie.modifiedTime) << endl;
                        outputFile << "-----------------------------" << endl;
                    cout << "Movie details saved to file successfully!" << endl;
                } else {
                    cout << "Unable to open the file!" << endl;
                }

                char modifyAgain;
                cout << "Do you want to modify another movie? (y/n): ";
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
        cout << "Movie not found." << endl;
        char searchAgain;
        cout << "Do you want to search for another movie to modify? (y/n): ";
        cin >> searchAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(searchAgain) == 'n') {
            // Close the file
            outputFile.close();
            return; // Exit the function
        } else {
            // Ask for another movie name and continue the loop
            cout << "Enter the name of the movie you want to modify: ";
            string newMovieName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, newMovieName);
            modifyMovie(newMovieName); // Recursive call to search for the new movie
        }
    }
}

void deleteMovie(string& movieName) {
    while (true) {
        auto it = find_if(movieList.begin(), movieList.end(),
                          [&movieName](const Movie& movie) { return movie.name == movieName; });

        if (it != movieList.end()) {
            time_t currentTime = time(0);
            it->deletedTime = currentTime;
            deletedMovies.push_back(*it);
            movieList.erase(it);

            cout << "Movie '" << movieName << "' deleted successfully." << endl;
            cout << "Deleted Time: " << ctime(&currentTime) << endl;
               cout << "Do you want to delete  another movie? (Y/N): ";
                char searchAgain;
                cin >> searchAgain;

                if (searchAgain == 'N' || searchAgain == 'n') {
                    break; // Exit the outer loop if the user doesn't want to search again
                } else {
                    cout << "Enter Movie Name to Delete: ";
                    cin.ignore(); // Clear input buffer
                    getline(cin, movieName);
                    continue; // Jump back to the beginning of the outer loop to search again
                }

            ofstream outputFile("C:/Users/Hassan/Desktop/Deleted_movies.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << "Movie Name: " << movieName << endl;
                outputFile << "Deleted Time: " << ctime(&currentTime) << endl;
                outputFile << "-----------------------------" << endl;
                outputFile.close();

                cout << "Movie details deleted from file successfully!" << endl;
                break; // Exit the loop after successful deletion
            } else {
                cout << "Unable to open the file!" << endl;
            }
        } else {
	
            cout << "Movie '" << movieName << "' not found in movie list." << endl;
            char retryChoice;
            cout << "Do you want to delete another movie? (Y/N): ";
            cin >> retryChoice;

            if (retryChoice == 'N' || retryChoice == 'n') {
                break; // Exit the loop if the user doesn't want to delete another movie
            } else {
                cout << "Enter Movie Name to delete: ";
                cin.ignore(); // Clear input buffer
                getline(cin, movieName);
            }
        }
    }
}

void restoreMovie( string& movieName) 
{
    while(true){
	
        auto it = find_if(deletedMovies.begin(), deletedMovies.end(),
                          [&movieName](const Movie& movie) { return movie.name == movieName; });

        if (it != deletedMovies.end()) {
        	   time_t currentTime = time(0);
            it->restoredTime = currentTime;
            movieList.push_back(*it);
            deletedMovies.erase(it);
            cout << "Movie '" << movieName << "' restored successfully." << endl;
            cout << "Restored Time: " << ctime(&currentTime) << endl;
              
            ofstream outputFile("C:/Users/Hassan/Desktop/Restored_movies.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << "Movie Name: " << movieName<< endl;
                outputFile << "Restored Time: " << ctime(&currentTime) << endl;
                outputFile << "-----------------------------" << endl;
                outputFile.close();

                cout << "Movie details deleted from file successfully!" << endl;
                cin.get();
            } else {
                cout << "Unable to open the file!" << endl;
            }
        } else {
            cout << "Movie '" << movieName << "' not found in deleted list." << endl;
              char retryChoice;
            cout << "Do you want to Restore another movie? (Y/N): ";
            cin >> retryChoice;

            if (retryChoice == 'N' || retryChoice == 'n') {
                break; // Exit the loop if the user doesn't want to delete another movie
            } else {
                cout << "Enter Movie Name to Restore: ";
                cin.ignore(); // Clear input buffer
                getline(cin, movieName);
            }
        }
    }
}



void sortMoviesBy(int choice) 
{
    switch (choice) 
	{
        case 1: // Sort by name
        
            sort(movieList.begin(), movieList.end(),[](const Movie& a, const Movie& b) {return a.name < b.name;});
            cout << "Movies sorted by name sucessfully." << endl;
            cin.get();
            break;

        case 2: // Sort by genre
            sort(movieList.begin(), movieList.end(),[](const Movie& a, const Movie& b) {return a.genre < b.genre;});
            cout << "Movies sorted by genre sucessfully." << endl;
            cin.get();
            break;

        case 3: // Sort by price
            sort(movieList.begin(), movieList.end(),[](const Movie& a, const Movie& b) {  return a.price < b.price; });
            cout << "Movies sorted by price sucessfully." << endl;
            cin.get();
            break;

        default:
            cout << "Invalid choice for sorting." << endl;
            cin.get();
            break;
    }
}

void searchMovieByName(string& movieName) {
    while (true) {
        bool found = false;

        for (const auto& movie : movieList) {
            if (movie.name == movieName) {
                found = true;
                // Display movie details
                cout << "Movie found:" << endl;
                cout << "Movie Name: " << movie.name << endl;
                cout << "Movie ID: " << movie.ID << endl;
                cout << "Genre: " << movie.genre << endl;
                cout << "Price: " << movie.price << endl;
                cout << "Release Date: " << movie.entryDate.day << "/" << movie.entryDate.month << "/" << movie.entryDate.year << endl;
                cout << "Goes Out Date: " << movie.exitDate.day << "/" << movie.exitDate.month << "/" << movie.exitDate.year << endl;
                cout << "Viewer Rating: " << movie.ratingPg << "/10" << endl;
                
                cout << "Registered Time: " << ctime(&movie.registerTime);
                if (movie.modifiedTime != 0) {
                    cout << "Modified Time: " << ctime(&movie.modifiedTime) << endl;
                } else {
                    cout << "Movie has not been modified yet." << endl;
                }
          
            }
        }

        if (!found) {
            cout << "Movie not found." << endl;
            cin.get();
        }
          cout << "-----------------------------" << endl;
        cout << "Do you want to search for another movie? (Y/N): ";
        char searchAgain;
        cin >> searchAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (searchAgain == 'N' || searchAgain == 'n') {
            break; // Exit the outer loop if the user doesn't want to search again
        } else {
            cout << "Enter Movie Name to search: ";
            getline(cin, movieName);
        } 
    }
}

void displayMovieListWithSlots() {
    cout << "Available Movies:" << endl;
    bool slotsAvailable = !movieSlots.empty();

    for (size_t i = 0; i < movieList.size(); ++i) {
        cout << "Movie: " << movieList[i].name;
        if (i < movieSlots.size()) {
            cout << " | Slot: " << movieSlots[i].slotNumber; // Display slot number
        } else {
            cout << " | Slot: N/A"; // No slot available for this movie
        }
        cout << endl;
    }

    if (!slotsAvailable) {
        cout << "No slots available yet." << std::endl;
    } else {
        ofstream outputFile("movie_slots.txt");

        if (outputFile.is_open()) {
            for (const auto& slot : movieSlots) {
                outputFile << "Movie Name: " << slot.movieName << " | Slot: " << slot.slotNumber << endl;
                outputFile << "-----------------------------" << endl;
            }
            outputFile.close();
            cout << "Movie slots saved to file successfully!" << endl;
            cin.get();
        } else {
            cout << "Unable to open the file!" << endl;
        }
    }
}
void addMovieAndSlot(const std::string& movieName, const std::string& MovieSlot);
};
#endif