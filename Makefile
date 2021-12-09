solver: main.cpp data/Cube.cpp data/Cube.h data/RingSet.cpp data/RingSet.h solving/Solver.h solving/Solver.cpp solving/BruteSolver.h solving/BruteSolver.cpp solving/DiffSolver.h solving/DiffSolver.cpp Options.h
	g++ main.cpp data/Cube.cpp data/RingSet.cpp solving/Solver.cpp solving/BruteSolver.cpp solving/DiffSolver.cpp -std=c++17 -O3 -o solver

solverd: main.cpp data/Cube.cpp data/Cube.h data/RingSet.cpp data/RingSet.h solving/Solver.h solving/Solver.cpp solving/BruteSolver.h solving/BruteSolver.cpp solving/DiffSolver.h solving/DiffSolver.cpp Options.h
	g++ main.cpp data/Cube.cpp data/RingSet.cpp solving/Solver.cpp solving/BruteSolver.cpp solving/DiffSolver.cpp -std=c++17 -O0 -g -o solverd

run: solver
	./solver

debug: solverd
	gdb ./solverd