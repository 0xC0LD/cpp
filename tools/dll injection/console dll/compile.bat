g++ -c -DBUILD_DLL main.cpp
g++ -Wa-shared -static -o console.dll main.o -Wl,--out-implib,libmain.a