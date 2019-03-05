all:
	g++ -std=c++11 -o scalefree scalefree.cpp network.h;
	g++ -std=c++11 -o scalefree_iterate scalefree_iterate.cpp network.h;
