#include "music_library.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void clearScreen()
{
    cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear terminal screen
}

void printMenu()
{
    cout << "+ ======================================================== +" << endl;
    cout << "|                    Music Library                         |" << endl;
    cout << "+ ======================================================== +" << endl;
    cout << "| Please choose an option:                                 |" << endl;
    cout << "| 1. Display all songs                                     |" << endl;
    cout << "| 2. Search for a song by title                            |" << endl;
    cout << "| 3. Search for a song by artist                           |" << endl;
    cout << "| 4. Remove Song by title                                  |" << endl;
    cout << "| 5. Exit                                                  |" << endl;
    cout << "+ ======================================================== +" << endl;
}

int main()
{

    clearScreen();
    string filename;
    bool exitProgram = false;

    do
    {
        cout << "+ ======================================================================= + " << endl;
        cout << "|                                 Welcome to                              |" << endl;
        cout << "|                            Music Library App                            |" << endl;
        cout << "|                                                                         |" << endl;
        cout << "+ ======================================================================= +" << endl;
        cout << "              Enter the name of the file to load (or 'exit' to quit)    " << endl;
        cout << "                                ";
        getline(cin, filename);

        if (filename == "exit")
        {
            exitProgram = true;
        }
        else if (filename.substr(filename.find_last_of(".") + 1) != "txt")
        {
            cout << "Error: File must be a .txt file." << endl;
        }
        else
        {
            MusicLibrary musicLibrary;
            musicLibrary.loadSongsFromFile(filename);
            cout << endl
                 << "These are the errors and have been skipped. If no error above file is in good format.Double Press enter to continue...";
            cin.ignore();
            cin.get();
            while (!exitProgram)
            {
                int choice;
                string searchQuery;
                string title;
                string artist;
                bool isSaved;
                clearScreen();
                printMenu();

                if (!(cin >> choice))
                {
                    cout << "Invalid input. Please enter a valid integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                switch (choice)
                {
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
                    cout << "Remove Song (REQUIRE Title & artist of the Song):" << endl;
                    cin.ignore();
                    cout << "Enter the title of the song: ";
                    getline(cin, title);
                    cout << "Enter the name of the artist: ";
                    getline(cin, artist);
                    musicLibrary.removeSong(title, artist);
                    break;

                case 5:
                    clearScreen();
                    int saveOption;
                    cout << "Do you want to save your changes? (1 for Yes / 2 for No): ";
                    cin >> saveOption;

                    if (saveOption == 1)
                    {
                        string saveOptionString;
                        cout << "Do you want to save to a new file or overwrite the current file? (new / overwrite): ";
                        cin >> saveOptionString;
                        while (saveOptionString != "new" && saveOptionString != "overwrite")
                        {
                            cout << "Invalid option. Please enter 'new' or 'overwrite': ";
                            cin >> saveOptionString;
                        }
                        if (saveOptionString == "new")
                        {
                            cout << "Enter the name of the new file to save: ";
                            string newFilename;
                            cin >> newFilename;
                            musicLibrary.saveSongsToFile(newFilename);
                        }
                        else
                        {
                            musicLibrary.saveSongsToFile(filename);
                        }
                        isSaved = true;
                    }
                    else
                    {
                        isSaved = true;
                    }

                    exitProgram = true;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }

                cout << endl
                     << "Double Press enter to continue...";
                cin.ignore();
                cin.get();
            }
        }

    } while (!exitProgram);

    clearScreen();
    cout << "Thank you for using Music Library! Goodbye!" << endl;
    return 0;
}
