g++ -c SendKeys.cpp -o SendKeys.o
g++ main.cpp -static-libgcc -static-libstdc++ SendKeys.o -o sndkw.exe
