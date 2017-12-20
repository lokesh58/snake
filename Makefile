headers=headers/*.h
sources=sources/*.cc

all: main object
	g++ *.o -o snake -std=c++14
	
main:
	g++ -c main.cc -std=c++14

object:
	g++ -c ${headers} ${sources} -std=c++14
