#include "music_library.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear terminal screen
}

void printMenu() {
    cout << "+ ======================================================== +" << endl;
    cout << "|                    Music Library                         |" << endl;
    cout << "+ ======================================================== +" << endl;
    cout << "| Please choose an option:                                 |" << endl;
    cout << "| 1. Display all songs                                     |" << endl;
    cout << "| 2. Search for a song by title                            |" << endl;
    cout << "| 3. Search for a song by artist                           |" << endl;
    cout << "| 4. Exit                                                  |" << endl;
    cout << "+ ======================================================== +" << endl;
}

int main() {
    clearScreen();
    string filename;
    bool exitProgram = false;

    do {
        cout << "+ ======================================================================= + "<< endl;
        cout << "|                                 Welcome to                              |"<< endl;
        cout << "|                            Music Library App                            |"<< endl;
        cout << "|                                                                         |"<< endl;
        cout << "+ ======================================================================= +"<< endl;
        cout << "              Enter the name of the file to load (or 'exit' to quit)    "<< endl;
        cout << "                                ";
        getline(cin, filename);

        if (filename == "exit") {
            exitProgram = true;
        } else if (filename.substr(filename.find_last_of(".") + 1) != "txt") {
            cout << "Error: File must be a .txt file." << endl;
        } else {
            MusicLibrary musicLibrary;
            musicLibrary.loadSongsFromFile(filename);
            
            while (!exitProgram) {
                int choice;
                string searchQuery;

                clearScreen();
                printMenu();

                if (!(cin >> choice)) {
                    cout << "Invalid input. Please enter a valid integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (choice) {
                    case 1:
                        clearScreen();
                        cout << "All Songs:" << endl;
                        musicLibrary.displaySongs();
                        break;
                    case 2:
                        clearScreen();
                        cout << "Search by Title:" << endl;
                        cin.ignore();
                        cout << "Enter the title of the song: ";
                        getline(cin, searchQuery);
                        musicLibrary.searchSongs(searchQuery);
                        break;
                    case 3:
                        clearScreen();
                        cout << "Search by Artist:" << endl;
                        cin.ignore();
                        cout << "Enter the name of the artist: ";
                        getline(cin, searchQuery);
                        musicLibrary.searchSongsArtist(searchQuery);
                        break;
                    case 4:
                        clearScreen();
                        exitProgram = true;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                
                cout << endl << "Double Press enter to continue...";
                cin.ignore();
                cin.get();
            }
        }

    } while (!exitProgram);

    clearScreen();
    cout << "Thank you for using Music Library! Goodbye!" << endl;
    return 0;
}
