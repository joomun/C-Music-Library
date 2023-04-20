#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map> // added this header

struct Song
{
    std::string title;
    std::string artist;
    int duration;

    Song();
    Song(const std::string &t, const std::string &a, int d);
};

struct TrieNode
{
    std::vector<Song *> songs;
    std::map<char, TrieNode *> children; 
    bool is_end_of_word;
};

class MusicLibrary
{
private:
    TrieNode *root_;
    std::map<std::string, Song *> songs_;

    TrieNode *createTrieNode();
    void insertSongInTrie(Song *song);
    void deleteTrie(TrieNode *node);
    void searchSongsInTrie(TrieNode *node, const std::string &query, int index, std::vector<Song *> &matchingSongs) const;
    void removeSongFromTrie(TrieNode *node, Song *song, const std::string &title, size_t index); // Change int to size_t
    std::vector<std::string> duplicate_songs_;
    void addSong(const std::string &title, const std::string &artist, int duration); // Add this line

public:
    MusicLibrary();
    ~MusicLibrary();
    void loadSongsFromFile(const std::string &filename);
    std::vector<Song> searchSongs(const std::string &searchQuery); // Change return type
    std::vector<Song> searchSongsArtist(const std::string &searchQuery); // Change return type
    void displaySongs() const;
    void removeSong(const std::string &title, const std::string &artist);
    void saveSongsToFile(const std::string &filename) const;
    void addSongsToLibraryFromFile(const std::string &additionalSongsFile);
    std::size_t size() const; // Add this line
};

#endif /* MUSIC_LIBRARY_H */
