windres res.rc -O coff -o res.res
gcc -c -DBUILD_DLL main.cpp
gcc -shared -static-libgcc -static-libstdc++ res.res main.o -Wl,--out-implib,libmessage.a -o main.dll