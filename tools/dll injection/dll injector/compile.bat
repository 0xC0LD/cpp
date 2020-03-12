:: mingw (32-bit)
g++ -Wall -static main.cpp -o ldll.exe

:: msys2 (32-bit & 64-bit)
g++32 -Wall -static main.cpp -o ldll32.exe
g++64 -Wall -static main.cpp -o ldll64.exe