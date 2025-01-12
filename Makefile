INCLUDES= -I ./include
LIBRARIES= -L ./lib 
FLAGS= -Wall -Wextra -Wno-error -g
MINGW32= -lmingw32 -lSDL2main -lSDL2
OBJECTS= ./build/chip8_memory.o

all: ${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} ${LIBRARIES} ${MINGW32}  -o ./bin/main

build/chip8_memory.o:src/chip8_memory.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8_memory.c -c -o ./build/chip8_memory.o

clean: 
	del build\*.o
	del bin\main.exe
