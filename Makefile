SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
#SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES = $(SRC_DIR)/lazyfoo08.cpp
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAGS = -lsdl2 -lSDL2_image

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)