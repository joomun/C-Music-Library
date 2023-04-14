#include "music_library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

Song::Song() : duration(0) {} // default constructor

Song::Song(const std::string& t, const std::string& a, int d) : title(t), artist(a), duration(d) {}

MusicLibrary::MusicLibrary() {} // Updated constructor

MusicLibrary::~MusicLibrary() {} // Updated destructor

void MusicLibrary::loadSongsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int line_num = 1;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, artist;
        int duration;

        std::getline(ss, title, '\t');
        std::getline(ss, artist, '\t');
        ss >> duration;

        if (!title.empty() && !artist.empty() && duration > 0) {
            Song song(title, artist, duration);
            std::string key = title + "|" + artist;
            struct SongKeyHash {
                std::size_t operator()(const std::string& key) const {
                    std::size_t h1 = std::hash<std::string>{}(key.substr(0, key.find('|')));
                    std::size_t h2 = std::hash<std::string>{}(key.substr(key.find('|') + 1));
                    return h1 ^ (h2 << 1);
                }
            };
            songs_[key] = song;
        } else {
            std::cerr << "Error on line " << line_num << ": Invalid song \"" << line << "\"" << std::endl;
        }
        line_num++;
    }

    file.close();
}

void MusicLibrary::displaySongs() {
    std::vector<std::string> invalid_songs;
    std::cout << "+------------------+------------------+------------------+" << std::endl;
    std::cout << "|      Title       |      Artist      |     Duration     |" << std::endl;
    std::cout << "+------------------+------------------+------------------+" << std::endl;
    for (const auto& song_pair : songs_) {
            const Song& song = song_pair.second;
            std::cout << "| " << std::setw(20) << std::left << song.title
                    << "| " << std::setw(16) << std::left << song.artist
                    << "| " << std::setw(16) << std::left << song.duration << "|" << std::endl;
        }
    std::cout << "+------------------+------------------+------------------+" << std::endl;

}


void MusicLibrary::searchSongs(const std::string& searchQuery) {
    std::vector<Song> matchingSongs;
    for (const auto& song_pair : songs_) {
        const Song& song = song_pair.second;
        if (song.title.find(searchQuery) != std::string::npos || song.artist.find(searchQuery) != std::string::npos) {
            matchingSongs.push_back(song);
        }
    }

    if (matchingSongs.empty()) {
        std::cout << "No songs found matching your query." << std::endl;
    } else {
        std::cout << "Songs matching your query:" << std::endl;
        std::cout << "+------------------+------------------+------------------+" << std::endl;
        std::cout << "|      Title       |      Artist      |     Duration     |" << std::endl;
        std::cout << "+------------------+------------------+------------------+" << std::endl;
        for (const auto& song : matchingSongs) {
            std::cout << "| " << std::setw(20) << std::left << song.title
                      << "| " << std::setw(16) << std::left << song.artist
                      << "| " << std::setw(16) << std::left << song.duration << "|" << std::endl;
        }
        std::cout << "+------------------+------------------+------------------+" << std::endl;
    }
}


