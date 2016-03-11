#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#ifndef NODE_H
#define NODE_H

using namespace std;
class node;

class res{ 
 public: 
	node* node1;	
	node* node2;	
	double value;
	string name;
	node* get_other_node(node* nodename);
};

class gcap{ 
 public: 
	node* node1;	
	double value;
	string name;
};

class ccap{ 
 public: 
	node* node1;	
	node* node2;	
	double value;
	string name;
	node* get_other_node(node* nodename);
};

class node{
 public:   
	node();
	node(string name);				// constructor
	~node() {};                                 	// destructor

	//list of resistance objects connected to this node
  	vector<res*> res_list;	

	//list of ground capacitances connected to this node		
  	vector<gcap*> gcap_list;			

	//list of coupling capacitnces connected to this node
  	vector<ccap*> ccap_list;			

	// Node state variables
   	string NodeName;
	int level;
	int tree_id;
	double current;
	double voltage;	

	// Functions to add resistance/capcitances (used during spef read)
	void add_res(string name,double value,node* node1);
	void add_gcap(string name,double value);
	void add_ccap(string name,double value,node* node1);
	
};

#endif
