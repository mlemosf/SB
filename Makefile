# MAKEFILE

CXX=g++

SRC=./src
BUILD_PATH=./build
INCLUDE=./include/
CFLAGS=-std=c++11 -Wall -g

TARGET=main

all: $(TARGET)

$(TARGET): $(SRC)/$(TARGET).cpp leitor.o
	$(CXX) $(CFLAGS) -o $(TARGET) $(SRC)/$(TARGET).cpp leitor.o

leitor.o: $(INCLUDE)/leitor.hpp $(SRC)/leitor.cpp cp_info.o
	$(CXX) $(CFLAGS) -c $(SRC)/leitor.cpp cp_info.o

cp_info.o: $(INCLUDE)/cp_info.hpp $(SRC)/cp_info.cpp
		$(CXX) $(CFLAGS) -c $(SRC)/cp_info.cpp

clean:
	rm *.o