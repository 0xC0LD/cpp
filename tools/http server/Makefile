OBJ := src/defaults.o src/error.o src/header.o src/request.o src/response.o src/server.o
CC := gcc
CFLAGS := -Wall -Werror -Wextra -lws2_32 -g
EXECUTABLE := server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE) $(CFLAGS)

clean:
	del "src\*.o" "$(EXECUTABLE).exe"