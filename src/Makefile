CXX      = g++
CXXFLAGS = -O2 -std=c++11 -g

all: ProvedRez

clean:
	rm -f ../bin/ProvedRez

ProvedRez: $(wildcard *.cpp) $(wildcard *.hpp)
	$(CXX) $(CXXFLAGS) $(wildcard *.cpp) $(wildcard *.hpp) -o ../bin/ProvedRez
