CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lws2_32
EXE    = http-server
OBJ    = src/tee.o src/request.o src/response.o src/server.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LIBS)

clean:
	del "src\*.o" "$(EXE).exe" "*.log"