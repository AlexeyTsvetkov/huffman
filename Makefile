CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -O2

CPP_FILES=$(wildcard src/*.cpp)

OBJ_FILES=$(CPP_FILES:.cpp=.o)

all: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o bin/arj

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	rm src/*.o
