CC = g++
FLAGS = -Wall -Werror -Wextra -static
EXE = admin

all:
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) main.cpp -o $(EXE) resources.res

clean:
	del "*.exe"