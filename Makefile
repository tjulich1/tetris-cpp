# OBJS specifies which files to compile as part of the project
OBJS = ./src/*.cpp

# CC specifies the compiler we are using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we will need
INCLUDE_PATHS = -I/usr/include/SDL2

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = 

# COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w #-Wl,-subsystem,windows

# LINKER_FLAGS specifies the libraries we are linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf

# OBJ_NAME specifies the name of our executable
OBJ_NAME = Tetris

# This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)