CC = g++
FLAGS = -Wall -Werror -Wextra -static
LIB = -lgdi32 -mwindows
EXE = SpamClicker

all:
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) main.cpp -o $(EXE) resources.res $(LIB)

clean:
	del "*.exe"