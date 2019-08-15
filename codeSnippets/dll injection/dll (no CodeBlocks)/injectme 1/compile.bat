gcc -c -DBUILD_DLL main.cpp
gcc -shared -static-libgcc -static-libstdc++ -o main.dll main.o -Wl,--out-implib,libmessage.a