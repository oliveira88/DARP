# CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
CC=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -pedantic -ggdb
OBJ=main.o
DEPS=main.hpp
TARGET=darp
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJ)
clean:
	rm -rf *.obj *.exe *.pdb *.ilk
