# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Directories
SRC_DIR := src
OBJ_DIR := obj

# Files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
MAIN_FILE := simulation.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
MAIN_OBJ := $(OBJ_DIR)/simulation.o

# Output
TARGET :=  oopproj_2025

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main file
$(OBJ_DIR)/simulation.o: $(MAIN_FILE) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rebuild
rebuild: clean all

.PHONY: all clean rebuild
