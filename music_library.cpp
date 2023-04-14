#include "music_library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>


const int INITIAL_CAPACITY = 10;

Song::Song() : duration(0) {} // default constructor

Song::Song(const std::string& t, const std::string& a, int d) : title(t), artist(a), duration(d) {}

MusicLibrary::MusicLibrary() {
    songs_ = new Song[INITIAL_CAPACITY];
    num_songs_ = 0;
    max_songs_ = INITIAL_CAPACITY;
}

MusicLibrary::~MusicLibrary() {
    delete[] songs_;
}

void MusicLibrary::loadSongsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int line_num = 1; // initialize line number to 1

    while (getline(file, line)) {
        if (num_songs_ == max_songs_) {
            Song* temp = new Song[max_songs_ * 2];
            for (int i = 0; i < max_songs_; i++) {
                temp[i] = songs_[i];
            }
            delete[] songs_;
            songs_ = temp;
            max_songs_ *= 2;
        }

        std::stringstream ss(line); // create stringstream object from line
        std::string title, artist;
        int duration;

        // extract title, artist, duration from stringstream object
        std::getline(ss, title, '\t');
        if (title.empty()) {
            std::cerr << "Error on line " << line_num << ": Missing title for song \"" << line << "\"" << std::endl;
            line_num++;
            continue;
        }
        std::getline(ss, artist, '\t');
        if (artist.empty()) {
            std::cerr << "Error on line " << line_num << ": Missing artist for song \"" << line << "\"" << std::endl;
            line_num++;
            continue;
        }
        ss >> duration;
        if (duration <= 0) {
            std::cerr << "Error on line " << line_num << ": Invalid duration for song \"" << line << "\"" << std::endl;
            line_num++;
            continue;
        }

        Song song(title, artist, duration);
        songs_[num_songs_] = song;
        num_songs_++;
        line_num++;
    }

    file.close();
}


void MusicLibrary::displaySongs() {
    std::vector<std::string> invalid_songs;
    std::cout << "+------------------+------------------+------------------+" << std::endl;
    std::cout << "|      Title       |      Artist      |     Duration     |" << std::endl;
    std::cout << "+------------------+------------------+------------------+" << std::endl;
    for (int i = 0; i < num_songs_; i++) {
        if (songs_[i].title.empty() || songs_[i].artist.empty() || songs_[i].duration <= 0) {
            std::string error_msg = "Error on line " + std::to_string(i+1) + ": Invalid song data";
            invalid_songs.push_back(error_msg);
            continue;
        }
        std::cout << "| " << std::setw(20) << std::left << songs_[i].title
                  << "| " << std::setw(16) << std::left << songs_[i].artist
                  << "| " << std::setw(16) << std::left << songs_[i].duration << "|" << std::endl;
    }
    std::cout << "+------------------+------------------+------------------+" << std::endl;

    // Display invalid songs
    if (!invalid_songs.empty()) {
        std::cout << std::endl << "Invalid songs:" << std::endl;
        std::cout << "+-----------------------+" << std::endl;
        std::cout << "|       Error Msg       |" << std::endl;
        std::cout << "+-----------------------+" << std::endl;
        for (const auto& invalid_song : invalid_songs) {
            std::cout << "| " << std::setw(22) << std::left << invalid_song << "|" << std::endl;
        }
        std::cout << "+-----------------------+" << std::endl;
    }
}


