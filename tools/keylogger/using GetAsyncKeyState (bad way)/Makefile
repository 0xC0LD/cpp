CC    = mingw32-g++
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE   = keylog

OBJ = capture.o

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) main.cpp -o $(EXE)
	$(CC) $(FLAGS) $(OBJ) main.cpp -o $(EXE)h -mwindows

clean:
	del "*.o" "*.exe"