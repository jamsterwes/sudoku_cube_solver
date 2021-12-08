solver: main.cpp Cube.cpp Cube.h RingSet.cpp RingSet.h Options.h
	g++ main.cpp Cube.cpp RingSet.cpp -O3 -o solver

run: solver
	./solver