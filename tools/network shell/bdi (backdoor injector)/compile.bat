:: debug
::g++ main.cpp -o bdi_debug.exe
:: release
windres resources.rc -O coff -o resources.res
g++ -Wall -static resources.res main.cpp -o bdi.exe