#include "music_library.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    system("cls");
    string filename;
    bool exitProgram = false;

    do {
        cout << "Enter the name of the file to load (or 'exit' to quit): ";
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

                cout << endl << "Please choose an option:" << endl;
                cout << "1. Display all songs" << endl;
                cout << "2. Search for a song by title" << endl;
                cout << "3. Search for a song by artist" << endl;
                cout << "4. Exit" << endl;

                if (!(cin >> choice)) {
                    
                    cout << "Invalid input. Please enter a valid integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (choice) {
                    case 1:
                        system("cls"); 
                        musicLibrary.displaySongs();
                        break;
                    case 2:
                        system("cls"); 
                        cin.ignore();
                        cout << "Enter title of song ";
                        getline(cin, searchQuery);
                        musicLibrary.searchSongs(searchQuery);
                        break;
                    case 3:
                        system("cls"); 
                        cin.ignore();
                        cout << "Enter name of artist: ";
                        getline(cin, searchQuery);
                        musicLibrary.searchSongsArtist(searchQuery);
                        break;
                    case 4:
                        system("cls"); 
                        exitProgram = true;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            }
        }

    } while (!exitProgram);

    return 0;
}
