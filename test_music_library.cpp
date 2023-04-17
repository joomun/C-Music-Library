#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() function
#include "catch.hpp"
#include "music_library.h"

TEST_CASE("Test song creation", "[Song]")
{
    Song song("Test Title", "Test Artist", 300);

    REQUIRE(song.title == "Test Title");
    REQUIRE(song.artist == "Test Artist");
    REQUIRE(song.duration == 300);
}

TEST_CASE("Test music library operations", "[MusicLibrary]")
{
    MusicLibrary musicLibrary;

    SECTION("Load songs from file")
    {
        musicLibrary.loadSongsFromFile("test_songs.txt");
        REQUIRE(musicLibrary.size() == 3); // Assuming the file has 3 songs
    }

    SECTION("Search songs")
    {
        Song song("Test Title", "Test Artist", 300);

        auto searchResults = musicLibrary.searchSongs("Test Title");
        REQUIRE(searchResults.size() == 1);
        REQUIRE(searchResults[0].title == "Test Title");
    }

    SECTION("Remove a song")
    {
        Song song("Test Title", "Test Artist", 300);

        musicLibrary.removeSong("Test Title", "Test Artist");
        REQUIRE(musicLibrary.size() == 0);
    }

    SECTION("Search by artist")
    {
        Song song("Test Title", "Test Artist", 300);

        auto searchResults = musicLibrary.searchSongsArtist("Test Artist");
        REQUIRE(searchResults.size() == 1);
        REQUIRE(searchResults[0].artist == "Test Artist");
    }

    SECTION("Save songs to file")
    {
        musicLibrary.saveSongsToFile("test_output.txt");
        MusicLibrary loadedMusicLibrary;
        loadedMusicLibrary.loadSongsFromFile("test_output.txt");
        REQUIRE(musicLibrary.size() == loadedMusicLibrary.size());
    }
}
