# Music Library

[![Build Status](https://travis-ci.org/your-username/your-repo.svg?branch=master)](https://travis-ci.org/your-username/your-repo)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A simple music library application written in C++. It allows you to manage a collection of songs and perform operations such as loading songs from a file, removing songs, and saving songs to a file.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Create a `Song` object with a title, artist, and duration.
- Manage a collection of songs using the `MusicLibrary` class.
- Load songs from a file into the music library.
- Remove songs from the library by title and artist.
- Save the songs in the library to a file.
- Unit tests for the `Song` and `MusicLibrary` classes using Catch.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/your-repo.git

2.Navigate to the project directory:
   cd your-repo

3.Compile the source code:
  
  g++ -std=c++11 -o music_library test_music_library.cpp music_library.cpp
  Make sure you have the necessary dependencies (Catch) installed

4. Run the test suite:
    
    ./music_library
    
    This will execute the unit tests and provide information about the passed and failed assertions.

Usage
To use the music library in your own project, you can include the necessary headers (music_library.h and song.h) and link against the compiled object files (music_library.o and song.o).

Here's a basic example of how to use the music library:

#include "music_library.h"

int main() {
    MusicLibrary musicLibrary;

    // Load songs from a file
    musicLibrary.loadSongsFromFile("songs.txt");

    // Perform operations on the music library
    // ...

    // Save the songs to a file
    musicLibrary.saveSongsToFile("output.txt");

    return 0;
}

Make sure to replace songs.txt and output.txt with the actual filenames.



