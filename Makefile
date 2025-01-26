UNAME := $(shell uname)

INCLUDES= -I ./include 

ifeq ($(UNAME), Linux)
INCLUDES+= -I ./usr/include/SDL2
endif

ifeq ($(UNAME), Windows)
LIBRARIES= -L ./lib
endif

FLAGS= -Wall -Wextra -Wno-error -g
MINGW32= -lSDL2main -lSDL2

ifeq ($(UNAME), Windows)
MINGW32+= -lmingw32
endif

OBJECTS= ./build/chip8_memory.o ./build/chip8_stack.o ./build/chip8_keyboard.o ./build/chip8.o ./build/chip8_screen.o
BUILD_DIR= build
TARGET = bin/main
ROM = bin/INVADERS

all: ${BUILD_DIR} ${OBJECTS}
	@echo "Operating System: $(UNAME)"
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} ${LIBRARIES} ${MINGW32} -o ./$(TARGET)

# Ensure the build directory exists
${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

# Object file targets
./build/chip8_memory.o: src/chip8_memory.c | ${BUILD_DIR}
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_memory.c -c -o ./build/chip8_memory.o

./build/chip8_stack.o: src/chip8_stack.c | ${BUILD_DIR}
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_stack.c -c -o ./build/chip8_stack.o

./build/chip8_keyboard.o: src/chip8_keyboard.c | ${BUILD_DIR}
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_keyboard.c -c -o ./build/chip8_keyboard.o

./build/chip8.o: src/chip8.c | ${BUILD_DIR}
	gcc ${FLAGS} ${INCLUDES} ./src/chip8.c -c -o ./build/chip8.o

./build/chip8_screen.o: src/chip8_screen.c | ${BUILD_DIR}
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_screen.c -c -o ./build/chip8_screen.o

run: all
	./$(TARGET) $(ROM)
clean: 
ifeq ($(UNAME), Linux)
	rm build/*.o
	rm bin/main
endif
ifeq ($(UNAME), Windows)
	del build\*.o
	del bin\main.exe
endif
