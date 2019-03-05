#include "network.h"
#include <iostream>

int main()
{
	int n = 10;
	int iterations=0;
	int converged;
	Network network;
	network.generate_scalefree(n,3,2);
	network.genstate_normal(0,1);
	
	double *oldstate = new double[n];
	
	std::cout << "The current state vector is:\n";
	network.print_state();

	std::cout << "\nNetwork adjacency is:\n";
	network.print_adjacency();

	do {
		converged = 1;
		for (int i=0;i<n;i++) { *(oldstate+i) = network.state[i]; } 
		network.iterate();
		for (int i=0;i<n;i++)
		{
			if ((float)network.state[i]!=(float)oldstate[i]) { converged = 0; }
		}
		iterations+=1;
	} while (iterations<=100000&&converged==0);
	
	std::cout << "\nAfter " << iterations-1 << " iterations, state is:\n";
	network.print_state();
}
