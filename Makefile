# MAKEFILE

CXX=g++

SRC=./src
BUILD_PATH=./build
INCLUDE=./include/
CFLAGS=-std=c++11 -Wall -g

TARGET=main

all: $(TARGET)

$(TARGET): $(SRC)/$(TARGET).cpp leitor.o cp_info.o
	$(CXX) $(CFLAGS) -o $(TARGET) $(SRC)/$(TARGET).cpp leitor.o exibidor.o cp_info.o

leitor.o: $(INCLUDE)/leitor.hpp $(SRC)/leitor.cpp
	$(CXX) $(CFLAGS) -c $(SRC)/leitor.cpp

exibidor.o: $(INCLUDE)/exibidor.hpp $(SRC)/exibidor.cpp
	$(CXX) $(CFLAGS) -c $(SRC)/exibidor.cpp

cp_info.o: $(INCLUDE)/cp_info.hpp $(SRC)/cp_info.cpp
		$(CXX) $(CFLAGS) -c $(SRC)/cp_info.cpp

clean:
	rm *.o