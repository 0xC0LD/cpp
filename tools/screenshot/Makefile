CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS = -lgdi32 -lgdiplus
EXE = ss

all:
	$(CC) $(FLAGS) main.c -o $(EXE) $(LIBS)

clean:
	del "*.exe"