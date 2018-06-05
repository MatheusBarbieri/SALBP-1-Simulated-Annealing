build:
		g++ -std=c++14 salbp1-simulated-annealing.cpp -o salbp1-sa

mock-run:
		./salbp1-sa "instances/MERTENS.IN2" 6 1 0.9 100 0.00001 0
