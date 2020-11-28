CC = g++
FLAGS_O = -c -DBUILD_DLL
FLAGS_X = -Wall -shared -static -Wl,--out-implib,
DLL = exit

all: main.cpp 
	$(CC) $(FLAGS_O) main.cpp -o main.o
	$(CC) $(FLAGS_X)main.a main.o -o $(DLL).dll
	
	$(CC)32 $(FLAGS_O) main.cpp -o main32.o
	$(CC)32 $(FLAGS_X)main32.a main32.o -o $(DLL)32.dll
	
	$(CC)64 $(FLAGS_O) main.cpp -o main64.o
	$(CC)64 $(FLAGS_X)main64.a main64.o -o $(DLL)64.dll
	
clean:
	del "*.dll" "*.o" "*.a"
