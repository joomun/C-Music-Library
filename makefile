# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

# Source files and object files
SRCS = main.cpp music_library.cpp
OBJS = $(SRCS:.cpp=.o)

# Test source files and object files
TEST_SRCS = test_music_library.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Target executable
TARGET = music
TEST_TARGET = test_music

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) music_library.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) music_library.o

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

clean_windows:
	del $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)


# Specify targets that don't correspond to file names
.PHONY: all clean test
