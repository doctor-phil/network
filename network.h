#ifndef NETWORK
#define NETWORK

#include <iostream>
#include <random>
#include <cmath>

class Network
{
	public:
		Network(void);                
		Network(int a);
		Network(const Network &net); 				//Copy Constructor
		~Network() { delete [] adjacency; delete [] state; }		//Destructor

									//Network Generators:
		void generate_scalefree(int a, int m0, int m);			//Scale-free generator (Barabasi-Albert Model)
		void generate_er(int a, double k);				//Erdos-Renyi generator
									
									//Output:
		void print_adjacency(void);					//Print adjacency matrix to stdout
		void print_state(void);
		void print_state(std::ostream& o);
		void print_adjacency(std::ostream& o);				//Print adjacency matrix to given output stream
		friend std::ostream& operator<<(std::ostream& os, Network& net);//<< operator

									//Simulate Dynamical Processes:
		void genstate_normal(double mean, double stddev);		//draw states for each node from iid normal dist
		void iterate(void);						//iterate dynamical process once
		void iterate(int k);						//iterate k times
	
									//Operations:
		double average_degree(void);
	
		int *adjacency;						//Stores adjacency matrix as nxn integer array
		double *state;						//Store the state vector of all nodes
		int n;							//Number of nodes in the network
};

Network::Network(void)							//init 10 node empty network
{
	n=10;
	state = new double[10];
	for (int i=0;i<10;i++) { state[i] = 0; }

	adjacency = new int[100];
	for (int i=0;i<100;i++) { adjacency[i] = 0; }
}

Network::Network(int a)							//init a node empty network
{
	n = a;
	state = new double[10];
	for (int i=0;i<10;i++) { state[i] = 0; }

	adjacency = new int[a];
	for (int i=0;i<a*a;i++) { adjacency[i] = 0; }
}

Network::Network(const Network &net)					//copy existing network
{
	n = net.n;
	state = new double[10];
	for (int i=0;i<10;i++) { state[i] = net.state[i]; }

	adjacency = new int[n*n];
	for (int i=0;i<n*n;i++) { adjacency[i] = net.adjacency[i]; }	
}

void Network::generate_scalefree(int a,int m0, int m)			//overwrite network with a randomly-drawn scale-free network
{
	n=a;
	delete [] adjacency;
	adjacency = new int [n*n];
	int k[n];
	double r;
	double prob;
	int node;
	double sum = m0 * m0 - m0;
	double newsum = sum;
	int num;

	for (int i=0;i<n;i++) { k[i]=0; }			

	for (int i=0;i<m0;i++)
	{
		k[i] = m0-1;
		for (int j=0;j<m0;j++)
		{
			if (j!=i&&j<m0&&i<m0) { *(adjacency+i*n+j) = 1; } else { *(adjacency+i*n+j)=0; } 
		}
	}

	std::random_device rd;
	std::mt19937 mt(rd());
  	std::uniform_real_distribution<double> distribution(0.0,1.0);

	for (int i=m0; i<n; i++)
	{
		num=0;
		
		do {
			node = (int)floor(distribution(mt)*(i+1));
			r = distribution(mt);
			prob = k[node] / sum;
			if (r<=prob && *(adjacency+i*n+node)!=1) 
			{ 
				*(adjacency+i*n+node)=1;
				*(adjacency+node*n+i)=1; 
				k[node]+=1;
				num+=1;
				newsum+=2;
			}
		} while (num<m);

		k[i] = m;
		sum=newsum;
	}
}

void Network::generate_er(int a, double k)				//overwrite network with a randomly drawn ER network
{
	n = a;
	delete [] adjacency;
	adjacency = new int[n*n];

	std::random_device device;
	std::mt19937 mt(device());
  	std::uniform_real_distribution<double> distribution(0.0,1.0);
	double draw;

	for (int i=0;i<n;i++)
	{
		*(adjacency+i*n+i)=0;

		for (int j=0;j<i;j++)
		{
			draw = distribution(mt);
			if (draw<k) { *(adjacency+j*n+i)=1; *(adjacency+i*n+j)=1; } else { *(adjacency+j*n+i)=0; *(adjacency+i*n+j)=0; }
		}
	}
}

void Network::print_adjacency(void) 
{
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			std::cout << (int)*(adjacency+i*n+j);
			if (j<(n-1)) { std::cout << ","; } else { std::cout << "\n"; }
		}
	}
}

void Network::print_adjacency(std::ostream& o) 
{
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			o << (int)*(adjacency+i*n+j);
			if (j<(n-1)) { o << ","; } else { o << "\n"; }
		}
	}
}

std::ostream& operator<<(std::ostream& o, Network& net)
{
	for (int i=0;i<net.n;i++)
	{
		for (int j=0;j<net.n;j++)
		{
			o << (int)net.adjacency[i*net.n+j];
			if (j<(net.n-1)) { o << ","; } else { o << "\n"; }
		}
	}
	return (o);
}

void Network::iterate(void)
{
	double sumelts=0;
	double *newstate;
	newstate = new double[n];

	for (int i=0;i<n;i++)
	{
		*(newstate+i)=0;
		for (int j=0;j<n;j++)
		{
			*(newstate+i)=(double)*(adjacency+i*n+j) * *(newstate+j);
			sumelts+=(double)*(adjacency+i*n+j);
		}
		*(newstate+i) = *(newstate+i)/sumelts;
		sumelts = 0;
	}
	for (int i=0;i<n;i++) { *(state+i)=*(newstate+i); }
}

void Network::iterate(int k)
{
	double sumelts=0;
	double *newstate;
	newstate = new double[n];
	for (int it=0;it<k;it++)
	{
		for (int i=0;i<n;i++)
		{
			*(newstate+i)=0;
			for (int j=0;j<n;j++)
			{
				*(newstate+i)=(double)*(adjacency+i*n+j) * *(newstate+j);
				sumelts+=(double)*(adjacency+i*n+j);
			}
			*(newstate+i) = *(newstate+i)/sumelts;
			sumelts = 0;
		}
		for (int i=0;i<n;i++) { *(state+i)=*(newstate+i); }
	}
}

void Network::genstate_normal(double mean, double stddev)
{
	std::random_device device;
	std::mt19937 mt(device());
	std::normal_distribution<double> distribution(mean,stddev);

	for (int i=0;i<n;i++)
	{
		*(state+i)=distribution(mt);
	}
}

double Network::average_degree(void)
{
	double k;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			k+=(double)*(adjacency+i*n+j);
		}
	}
	return k/(double)n;
}

void Network::print_state(void)
{
	for (int i=0;i<n;i++)
	{
		std::cout << (double)*(state+i);
		if (i<(n-1)) { std::cout << ","; }
	}
}

void Network::print_state(std::ostream& o)
{
	for (int i=0;i<n;i++)
	{
		o << (double)*(state+i);
		if (i<(n-1)) { o << ","; }
	}
}
#endif
