CC = g++
FLAGS = -Wall -Werror -Wextra -static -Os -s
EXE = bdi

all:
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) main.cpp -o $(EXE) resources.res

clean:
	del "*.exe"