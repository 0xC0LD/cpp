:: debug compile
g++ -Wall -D DEBUG main.cpp -lgdi32 -lwinmm -lwininet -lws2_32 -o shell_debug.exe

:: release compile (no admin)
g++ -Wall -static main.cpp -lgdi32 -lwinmm -lwininet -lws2_32 -mwindows -o shell_release.exe

:: release compile (admin)
windres resources.rc -O coff -o resources.res
g++ -Wall -static main.cpp resources.res -lgdi32 -lwinmm -lwininet -lws2_32 -mwindows -o shell_release_admin.exe
