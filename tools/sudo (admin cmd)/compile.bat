windres resources.rc -O coff -o resources.res
g++ -Wall -static main.cpp resources.res -o sudo.exe