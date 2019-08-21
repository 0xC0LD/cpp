g++ -c -DBUILD_DLL main.cpp
g++ -shared -static-libgcc -static-libstdc++ -o main.dll main.o -Wl,--out-implib,libmain.a