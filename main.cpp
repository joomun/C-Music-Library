#include "music_library.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
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

            int choice;
            string searchQuery;

            cout << endl << "Please choose an option:" << endl;
            cout << "1. Display all songs" << endl;
            cout << "2. Search for a song" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    musicLibrary.displaySongs();
                    break;
                case 2:
                    cin.ignore();
                    cout << "Enter a search query: ";
                    getline(cin, searchQuery);
                    musicLibrary.searchSongs(searchQuery);
                    break;
                case 3:
                    exitProgram = true;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }

    } while (!exitProgram);

    return 0;
}
