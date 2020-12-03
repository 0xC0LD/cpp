CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE = sudo

all:
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) main.c -o $(EXE) resources.res

clean:
	del "*.exe"