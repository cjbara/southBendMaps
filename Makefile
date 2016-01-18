CXX=g++
CC=gcc
CXXFLAGS=-std=c++11 -O3

all: route test1 test3 test4 test5a test5b measure

route: route.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@

test1: test1.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@
test3: test3.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@
test4: test4.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@
test5a: test5a.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@
test5b: test5b.o street_map.o street_map.hpp graph.o
	$(CXX) $(CXXFLAGS) $< street_map.o graph.o -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

measure: measure.c
	$(CC) $< -o $@
clean:
	rm -rf route test1 test3 test4 test5a test5b measure *.exe *.o *.dSYM gmon.out *~

