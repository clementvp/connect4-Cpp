# Makefile for Connect4 Library Test

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
SRCDIR = src
TESTDIR = test
TARGET = test_connect4

# Source files
SOURCES = $(SRCDIR)/Connect4.cpp $(SRCDIR)/Connect4AI.cpp
TEST_SOURCES = $(TESTDIR)/test_connect4.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Main target
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files
$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests
test: $(TARGET)
	@echo "Running tests..."
	@./$(TARGET)

# Clean
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Rebuild
rebuild: clean all

.PHONY: all test clean rebuild
