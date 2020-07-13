:: mingw (32-bit)
g++ -c -DBUILD_DLL main.cpp -o main.o
g++ -Wall -shared -static -o crash.dll main.o -Wl,--out-implib,libmain.a

:: msys2 (32-bit & 64-bit)
g++32 -c -DBUILD_DLL main.cpp -o main32.o
g++32 -Wall -shared -static -o crash32.dll main32.o -Wl,--out-implib,libmain32.a

g++64 -c -DBUILD_DLL main.cpp -o main64.o
g++64 -Wall -shared -static -o crash64.dll main64.o -Wl,--out-implib,libmain64.a