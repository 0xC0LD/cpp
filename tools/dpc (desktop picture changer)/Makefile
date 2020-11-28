CC := g++
CFLAGS := -Wall -Werror -Wextra -static
EXECUTABLE := dpc

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXECUTABLE)
	
all: main.o

clean:
	del "*.exe"