# MAKEFILE

CXX=g++

SRC=./src
BUILD_PATH=./build
INCLUDE=./include
CFLAGS=-std=c++11 -Wall -g

TARGET=main

all: $(TARGET)
	rm -f *.o *~

$(TARGET): $(SRC)/$(TARGET).cpp exibidor.o leitor.o cp_info.o method_info.o attribute_info.o
	$(CXX) $(CFLAGS) -o $(TARGET) $(SRC)/$(TARGET).cpp exibidor.o leitor.o cp_info.o method_info.o attribute_info.o

leitor.o: $(INCLUDE)/leitor.hpp $(SRC)/leitor.cpp
	$(CXX) $(CFLAGS) -c $(SRC)/leitor.cpp

exibidor.o: $(INCLUDE)/exibidor.hpp $(SRC)/exibidor.cpp
	$(CXX) $(CFLAGS) -c $(SRC)/exibidor.cpp

cp_info.o: $(INCLUDE)/cp_info.hpp $(SRC)/cp_info.cpp
		$(CXX) $(CFLAGS) -c $(SRC)/cp_info.cpp

method_info.o: $(INCLUDE)/method_info.hpp $(SRC)/method_info.cpp
		$(CXX) $(CFLAGS) -c $(SRC)/method_info.cpp

attribute_info.o: $(INCLUDE)/attribute_info.hpp $(SRC)/attribute_info.cpp
		$(CXX) $(CFLAGS) -c $(SRC)/attribute_info.cpp