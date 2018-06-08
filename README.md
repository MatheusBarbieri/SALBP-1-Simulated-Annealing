# SALBP-1-Simulated-Annealing

This algorithm is a probabilistic approach for approximating the global optimum of Simple Assembly Line Balancing Problem.

## Linux build

To build this application execute `make build` in the parent directory.

## Usage
```
./salbp1-sa[OPTIONS]...
	OPTIONS:
		-c <cycle_time>           (SALBP1 maximum time per station. Default: 6)
		-t <temperature>          (initial temperature. Default: 1)
		-l <temperature_limit>    (stop condition. Default: 0.000001)
		-d <temperature_decay>    (cools temperature to (temperature_decay*temperature) every n iterations. Default 0.9)
		-i <iterations>           (number of iterations before cooling. Default: 1000)
		-s <Seed>                 (seed Number. Default: Time based pseudo-random integer)
		-v                        (verbose. Not activated by default)
```
