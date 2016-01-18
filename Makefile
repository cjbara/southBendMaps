CXX=g++
CXXFLAGS=-std=c++11 -O3

all: route

route: route.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@

clean:
	rm -rf route *.o

