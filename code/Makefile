OBJS = handmade.cpp

CC = g++
COMPILER_FLAGS = -w `sdl2-config --cflags --libs` -g
LINKER_FLAGS =

OBJ_NAME = ../build/handmade

all: run

compile: $(OBJS)
	mkdir -p ../build
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: compile
	./$(OBJ_NAME)
