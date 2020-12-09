CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
FLAGS_O = -c -DBUILD_DLL
FLAGS_X = -Wall -shared -static -Wl,--out-implib,
DLL = crash

all: main.c 
	$(CC) $(FLAGS_O) main.c -o main.o
	$(CC) $(FLAGS_X)main.a main.o -o $(DLL).dll
	
	$(CC32) $(FLAGS_O) main.c -o main32.o
	$(CC32) $(FLAGS_X)main32.a main32.o -o $(DLL)32.dll
	
	$(CC64) $(FLAGS_O) main.c -o main64.o
	$(CC64) $(FLAGS_X)main64.a main64.o -o $(DLL)64.dll
	
clean:
	del "*.dll" "*.o" "*.a"