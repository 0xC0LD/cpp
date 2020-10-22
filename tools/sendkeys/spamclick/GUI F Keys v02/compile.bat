windres resources.rc -O coff -o resources.res
g++ -Wall -static main.cpp -o SpamClicker.exe -lgdi32 resources.res -mwindows
