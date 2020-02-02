g++ -c -DBUILD_DLL main.cpp
g++ -Wall -shared -static -o exit.dll main.o -Wl,--out-implib,libmain.a