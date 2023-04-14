CC=g++
CFLAGS=-Wall -Werror -std=c++11
LDFLAGS=

SOURCES=main.cpp music_library.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=music_library

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(CFLAGS) $(OBJECTS) -o $@

.cpp.o:
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -rf $(OBJECTS) $(EXECUTABLE)
