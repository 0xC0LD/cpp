CC = g++
FLAGS_O = -c -DBUILD_DLL
FLAGS_X = -Wall -shared -static -Os -s -Wl,--out-implib,main
LIBS = -lwinmm
DLL = music

all: main.cpp 
	$(CC) $(FLAGS_O) main.cpp -o main.o
	$(CC) $(FLAGS_X).a main.o -o $(DLL).dll $(LIBS)
	
	$(CC)32 $(FLAGS_O) main.cpp -o main32.o
	$(CC)32 $(FLAGS_X)32.a main32.o -o $(DLL)32.dll $(LIBS)
	
	$(CC)64 $(FLAGS_O) main.cpp -o main64.o
	$(CC)64 $(FLAGS_X)64.a main64.o -o $(DLL)64.dll $(LIBS)
	
clean:
	del "*.dll" "*.o" "*.a"
