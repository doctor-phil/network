#ifndef SCALEFREE
#define SCALEFREE
#include <iostream>

#include <random>
#include <cmath>

class Scalefree
{
	public:
	Scalefree(void);
	Scalefree(int a,int m0, int m);
	~Scalefree() { delete adjacency; };
	void PrintG(void);
	void PrintG(std::ostream& o);

	int *adjacency;
	int n;
	int m0;
	int m;
};

Scalefree::Scalefree(void)
{
	n=1;
	adjacency = new int[1];
	*adjacency = 0;
}

Scalefree::Scalefree(int a,int m_0, int em)
{
	m0 = m_0;
	m = em;
	n=a;
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

void Scalefree::PrintG(void) 
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

void Scalefree::PrintG(std::ostream& o) 
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

#endif
