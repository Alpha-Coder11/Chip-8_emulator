INCLUDES= -I ./include
LIBRARIES= -L ./lib 
FLAGS= -Wall -Wextra -Wno-error -g
MINGW32= -lmingw32 -lSDL2main -lSDL2
all:
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${LIBRARIES} ${MINGW32}  -o ./bin/main