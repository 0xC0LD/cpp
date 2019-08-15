windres resources.rc -O coff -o resources.res
g++ main.cpp resources.res -static-libgcc -static-libstdc++ -o sudo.exe