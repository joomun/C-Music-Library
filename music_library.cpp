#include "music_library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

Song::Song() : duration(0) {} // default constructor

Song::Song(const std::string& t, const std::string& a, int d) : title(t), artist(a), duration(d) {}

MusicLibrary::MusicLibrary() {
    root_=createTrieNode();
} // Updated constructor

MusicLibrary::~MusicLibrary() {
    deleteTrie(root_);
} // Updated destructor

TrieNode* MusicLibrary::createTrieNode() {
    TrieNode* node = new TrieNode;
    node->is_end_of_word = false;
    return node;
}




void MusicLibrary::insertSongInTrie(Song* song) {
    TrieNode* current = root_;
    for (char ch : song->title) {
        ch = tolower(ch);
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = createTrieNode();
        }
        current = current->children[ch];
    }
    current->is_end_of_word = true;
    current->songs.push_back(song);
}


void MusicLibrary::searchSongsInTrie(TrieNode* node, const std::string& query, int index, std::vector<Song*>& matchingSongs) const{
    if (node->is_end_of_word) {
        for (Song* song : node->songs) {
            matchingSongs.push_back(song);
        }
    }

    if (index == query.length()) {
        return;
    }

    char ch = tolower(query[index]);
    if (node->children.find(ch) != node->children.end()) {
        searchSongsInTrie(node->children[ch], query, index + 1, matchingSongs);
    }
}

void MusicLibrary::deleteTrie(TrieNode* node) {
    for (auto& child : node->children) {
        deleteTrie(child.second);
    }
    delete node;
}

void MusicLibrary::loadSongsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: failed to open file " << filename << std::endl;
        return;
    }
    std::string line;
    int line_num = 1;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, artist;
        int duration;

        std::getline(ss, title, '\t');
        std::getline(ss, artist, '\t');
        ss >> duration;
        ss.clear();

        if (!title.empty() && !artist.empty() && duration > 0) {
            Song* song = new Song(title, artist, duration);
            std::string key = title + "|" + artist; // Create the key
            songs_[key] = song; // Add a pointer to the song to the map
            insertSongInTrie(song); // Insert the song into the trie
            
        } else {
            std::cerr << "Error on line " << line_num << ": Invalid song \"" << line << "\"" << std::endl;
        }
        line_num++;
    }

    file.close();
}





void MusicLibrary::searchSongs(const std::string& searchQuery) {
    std::vector<Song*> matchingSongs;
    TrieNode* current = root_;
    for (char ch : searchQuery) {
        ch = tolower(ch);
        if (current->children.find(ch) == current->children.end()) {
            std::cout << "No songs found matching your query." << std::endl;
            return;
        }
        current = current->children[ch];
    }
    searchSongsInTrie(current, searchQuery, searchQuery.length(), matchingSongs);

    if (matchingSongs.empty()) {
        std::cout << "No songs found matching your query." << std::endl;
    } else {
        std::cout << "Songs matching your query:" << std::endl;
        std::cout << "+------------------+------------------+------------------+" << std::endl;
        std::cout << "|      Title       |      Artist      |     Duration     |" << std::endl;
        std::cout << "+------------------+------------------+------------------+" << std::endl;
        for (const auto& song : matchingSongs) {
            std::cout << "| " << std::setw(20) << std::left << song->title
                      << "| " << std::setw(16) << std::left << song->artist
                      << "| " << std::setw(16) << std::left << song->duration << "|" << std::endl;
        }
        std::cout << "+------------------+------------------+------------------+" << std::endl;
    }
}



void MusicLibrary::displaySongs() const {
    std::vector<Song*> allSongs;
    for (auto& song : songs_) {
        allSongs.push_back(song.second);
    }

    if (allSongs.empty()) {
        std::cout << "No songs in the library." << std::endl;
    } else {
        std::cout << "+------------------+------------------+------------------+" << std::endl;
        std::cout << "|      Title       |      Artist      |     Duration     |" << std::endl;
        std::cout << "+------------------+------------------+------------------+" << std::endl;
        for (const auto& song : allSongs) {
            std::cout << "| " << std::setw(20) << std::left << song->title
                      << "| " << std::setw(16) << std::left << song->artist
                      << "| " << std::setw(16) << std::left << song->duration << "|" << std::endl;
        }
        std::cout << "+------------------+------------------+------------------+" << std::endl;
    }
}

void MusicLibrary::searchSongsArtist(const std::string& searchQuery) {
    std::vector<Song*> matchingSongs;
    for (auto& song : songs_) {
    if (song.second->artist.find(searchQuery) != std::string::npos) {
    matchingSongs.push_back(song.second);
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
                std::cout << "| " << std::setw(20) << std::left << song->title
                        << "| " << std::setw(16) << std::left << song->artist
                        << "| " << std::setw(16)<<std::left << song->duration << "|" << std::endl;}
                std::cout << "+------------------+------------------+------------------+" << std::endl;
}
}
