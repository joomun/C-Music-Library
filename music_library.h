#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include <string>
#include <sstream> // added header

struct Song {
    std::string title;
    std::string artist;
    int duration;

    Song(); // added default constructor
    Song(const std::string& t, const std::string& a, int d);
};

class MusicLibrary {
public:
    MusicLibrary();
    ~MusicLibrary();

    void loadSongsFromFile(const std::string& filename);
    void displaySongs();
    void searchSongs(const std::string& searchQuery);


private:
    Song* songs_;
    int num_songs_;
    int max_songs_;
};

#endif
