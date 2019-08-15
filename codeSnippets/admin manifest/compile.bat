windres resources.rc -O coff -o resources.res
g++ main.cpp resources.res -o admin.exe