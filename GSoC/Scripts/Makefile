simul : first_sim_functions.o first_simulator.o
	g++ -L/opt/local/lib -o simul first_sim_functions.o first_simulator.o -lsbml

first_simulator.o : first_simulator.cpp first_sim_functions.hpp
	g++ -I/opt/local/include -c first_simulator.cpp

first_sim_functions.o : first_sim_functions.cpp
	g++ -I/opt/local/include -c first_sim_functions.cpp

clean:
	rm first_sim_functions.o first_simulator.o simul