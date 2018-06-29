CXX = g++ -std=c++11 -Wall

test: sim
	  ./sim

sim: sim.cpp
	${CXX} sim.cpp -o sim

clean:
	rm -f sim
