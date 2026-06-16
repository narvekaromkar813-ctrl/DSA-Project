# Makefile for Smart Defense Surveillance & Border Security Intelligence System
# Usage:
#   make          -> builds the "sds" executable
#   make run      -> builds (if needed) and runs the executable
#   make clean    -> removes build artifacts

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
SRC      := src/main.cpp
TARGET   := sds

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC) include/*.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
