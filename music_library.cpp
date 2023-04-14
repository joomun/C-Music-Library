#include "music_library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include <map> // add this line


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
    std::map<std::string, Song*> temp_songs; // temporary map to store lowercase key-value pairs
    std::set<std::string> seen_songs; // to keep track of songs that have already been loaded

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, artist;
        int duration;

        std::getline(ss, title, '\t');
        std::getline(ss, artist, '\t');
        ss >> duration;
        ss.clear();

        if (!title.empty() && !artist.empty() && duration > 0) {
            std::string key = title + "|" + artist;
            std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); }); // convert key to lowercase
            if (temp_songs.count(key) == 0 && songs_.count(key) == 0 && seen_songs.count(key) == 0) { // check if the song is already in the map or has already been loaded
                Song* song = new Song(title, artist, duration);
                songs_[key] = song; // Add a pointer to the song to the map
                temp_songs[key] = song; // Add a pointer to the temporary map
                insertSongInTrie(song); // Insert the song into the trie
                seen_songs.insert(key); // Add the song to the set of seen songs
            } else if (temp_songs.count(key) > 0 || songs_.count(key) > 0) { // song already exists in the map or temporary map
                if (std::find(duplicate_songs_.begin(), duplicate_songs_.end(), key) == duplicate_songs_.end()) {
                    duplicate_songs_.push_back(key);
                    std::cerr << "Warning on line " << line_num << ": Duplicate song \"" << line << "\"" << std::endl;
                }
            } // else: song has already been loaded from a previous line, skip it
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

void MusicLibrary::removeSongFromTrie(TrieNode* node, Song* song, const std::string& title, int index) {
    if (index == title.length()) {
        node->is_end_of_word = false;
        auto it = std::find_if(node->songs.begin(), node->songs.end(),
                               [song](Song* s) { return s->title == song->title && s->artist == song->artist; });
        if (it != node->songs.end()) {
            node->songs.erase(it);
        }
        return;
    }

    char ch = tolower(title[index]);
    if (node->children.find(ch) != node->children.end()) {
        removeSongFromTrie(node->children[ch], song, title, index + 1);
        if (node->children[ch]->children.empty() && !node->children[ch]->is_end_of_word) {
            delete node->children[ch];
            node->children.erase(ch);
        }
    }
}



void MusicLibrary::removeSong(const std::string& title, const std::string& artist) {
    std::string key = title + "|" + artist;
    auto it = songs_.find(key);
    if (it != songs_.end()) {
        Song* song = it->second;
        // Remove the song from the trie
        removeSongFromTrie(root_, song, title, 0);
        // Remove the song from the map
        songs_.erase(it);
        delete song;
        std::cout << "Song \"" << title << "\" by \"" << artist << "\" removed from the library." << std::endl;
    } else {
        std::cout << "Song \"" << title << "\" by \"" << artist << "\" not found in the library." << std::endl;
    }
}


void MusicLibrary::saveSongsToFile(const std::string& filename) const {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (auto const& song : songs_) {
        outfile << song.second->title << "\t" << song.second->artist << "\t" << song.second->duration << std::endl;
    }

    outfile.close();
    std::cout << "Song data saved to file: " << filename << std::endl;
}
