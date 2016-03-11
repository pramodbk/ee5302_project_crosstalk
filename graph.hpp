#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#include"node.hpp"
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
class graph{
 public:   
	graph();
	~graph() {};                                 	// destructor

	// graph state variables
	int inputs;

	// Hash of nodes in the graph by name
	map<string,node*> node_map; 

	// Add node by name
	void add_node(string name);

	// Adds res/cap using between 2 nodes (used during spef read)
	void add_res(string name,double value,node* node1,node* node2);
	void add_gcap(string name,double value,node* node1);
	void add_ccap(string name,double value,node* node1,node* node2);

	void calculate_moments(int tree,int nodename);

	void levelize();

	// vector of vector of node
	// 1 vector per resistance tree
	vector< vector<node*> > level_order;
	
};

#endif
