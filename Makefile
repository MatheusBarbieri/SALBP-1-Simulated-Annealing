build:
		g++ -std=c++14 salbp1-simulated-annealing.cpp -o salbp1-sa

clean:
	rm -rf salbp1-sa-outputs/*

run: clean build
	python runner.py
