#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include <string>
#include <vector>
#include <unordered_map>

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
    std::unordered_map<char, TrieNode *> children;
    std::vector<Song *> songs;
    bool is_end_of_word;
};

class MusicLibrary
{
private:
    TrieNode *root_;
    std::unordered_map<std::string, Song *> songs_;

    TrieNode *createTrieNode();
    void insertSongInTrie(Song *song);
    void deleteTrie(TrieNode *node);
    void searchSongsInTrie(TrieNode *node, const std::string &query, int index, std::vector<Song *> &matchingSongs) const;
    void removeSongFromTrie(TrieNode *node, Song *song, const std::string &title, int index);
    std::vector<std::string> duplicate_songs_;
    void addSong(const std::string &title, const std::string &artist, int duration); // Add this line

public:
    MusicLibrary();
    ~MusicLibrary();
    void loadSongsFromFile(const std::string &filename);
    void searchSongs(const std::string &searchQuery);
    void searchSongsArtist(const std::string &searchQuery);
    void displaySongs() const;
    void removeSong(const std::string &title, const std::string &artist);
    void saveSongsToFile(const std::string &filename) const;
    void addSongsToLibraryFromFile(const std::string &additionalSongsFile);
};


struct SongKeyHash
{
    std::size_t operator()(const std::string &key) const
    {
        return std::hash<std::string>()(key);
    }
};

#endif /* MUSIC_LIBRARY_H */
