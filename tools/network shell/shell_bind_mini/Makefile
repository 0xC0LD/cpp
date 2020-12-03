CC = gcc
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIB = -lws2_32
EXE = shell

debug:
	$(CC) $(FLAGS) main.c -o $(EXE)_debug $(LIB) -D DEBUG 

release:
	$(CC) $(FLAGS) main.c -o $(EXE)_release $(LIB) -mwindows

release_admin:
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) main.c -o $(EXE)_release_admin $(LIB) -mwindows resources.res

all: debug release release_admin

clean:
	del "*.exe"
