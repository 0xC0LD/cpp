:: mingw (32-bit)
g++ -c -DBUILD_DLL main.cpp
g++ -Wall -shared -static -o console.dll main.o -Wl,--out-implib,libmain.a

:: msys2 (32-bit & 64-bit)
g++32 -c -DBUILD_DLL main.cpp
g++32 -Wall -shared -static -o console32.dll main.o -Wl,--out-implib,libmain.a

g++64 -c -DBUILD_DLL main.cpp
g++64 -Wall -shared -static -o console64.dll main.o -Wl,--out-implib,libmain.a