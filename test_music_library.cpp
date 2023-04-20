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

        INFO("Load songs from file passed");
    }

    SECTION("Remove a song")
    {
        Song song("Test Title", "Test Artist", 300);

        musicLibrary.removeSong("Test Title", "Test Artist");
        REQUIRE(musicLibrary.size() == 0);
    
        INFO("Remove a song passed");
    }

    SECTION("Save songs to file")
    {
        musicLibrary.loadSongsFromFile("test_songs.txt");

        musicLibrary.saveSongsToFile("test_output.txt");
        MusicLibrary loadedMusicLibrary;
        loadedMusicLibrary.loadSongsFromFile("test_output.txt");
        REQUIRE(musicLibrary.size() == loadedMusicLibrary.size());

        INFO("Save songs to file passed");
    }
    
}

