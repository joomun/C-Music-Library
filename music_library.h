#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include <string>
#include <sstream>
#include <unordered_map>

struct Song {
    std::string title;
    std::string artist;
    int duration;

    Song();
    Song(const std::string& t, const std::string& a, int d);
};

class MusicLibrary {
public:
    MusicLibrary(); // Updated constructor
    ~MusicLibrary(); // Updated destructor
    void loadSongsFromFile(const std::string& filename);
    void displaySongs();
    void searchSongs(const std::string& searchQuery);

private:
    std::unordered_map<std::string, Song> songs_; // Changed to std::unordered_map
};

struct SongKeyHash {
    std::size_t operator()(const std::string& key) const {
        std::size_t h1 = std::hash<std::string>{}(key.substr(0, key.find('|')));
        std::size_t h2 = std::hash<std::string>{}(key.substr(key.find('|') + 1));
        return h1 ^ (h2 << 1);
    }
};

#endif
