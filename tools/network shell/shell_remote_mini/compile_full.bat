g++ -Wall -D DEBUG main.cpp -lws2_32 -o shell_debug.exe
g++ -Wall -static main.cpp -lws2_32 -mwindows -o shell_release.exe
windres resources.rc -O coff -o resources.res
g++ -Wall -static main.cpp resources.res -lws2_32 -mwindows -o shell_release_admin.exe