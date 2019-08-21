g++ -c -DBUILD_DLL main.cpp
g++ -shared -static-libgcc -static-libstdc++ -o console.dll main.o -Wl,--out-implib,libmain.a