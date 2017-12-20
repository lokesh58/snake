headers=headers/*.h
sources=headers/*.cc

all: main object
	g++ *.o -o snake
	
main:
	g++ -c main.cc

object:
	g++ -c ${headers} ${sources}
