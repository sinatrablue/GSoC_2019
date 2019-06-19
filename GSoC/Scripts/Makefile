simul : first_sim_functions.o first_simulator.o
	g++ -o simul first_sim_functions.o first_simulator.o -lsbml

first_simulator.o : first_simulator.cpp first_sim_functions.hpp
	g++ -c first_simulator.cpp

first_sim_functions.o : first_sim_functions.cpp
	g++ -c first_sim_functions.cpp
