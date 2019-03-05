#include "network.h"
#include <iostream>

int main()
{
	Network network;
	network.generate_scalefree(10,3,2);
	network.genstate_normal(10,500);
	
	std::cout << "The current state vector is:\n";
	network.print_state();

	std::cout << "\nNetwork adjacency is:\n";
	network.print_adjacency();

	network.iterate();
	std::cout << "\nAfter 1 iterations, state is:\n";
	network.print_state();
}
