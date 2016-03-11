#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#include"node.hpp"

using namespace std;

node::node()  { } 
node::node(string name) 
{
	NodeName = name;  
	level = -1;
	tree_id = -1;
};   						
void node::add_res(string name,double value,node* node1)
{
	res *res_temp = new res;
	res_temp->node1 = this;
	res_temp->node2 = node1;
	res_temp->value = value;
	res_temp->name = name;
	this->res_list.push_back(res_temp);
  	node1->res_list.push_back(res_temp);
	
}						
node* res::get_other_node(node* nodename)
{
	if (nodename == node1) { 
		return node2;
	} else {
		return node1;
	}
}
node* ccap::get_other_node(node* nodename)
{
	if (nodename == node1) { 
		return node2;
	} else {
		return node1;
	}
}
void node::add_gcap(string name,double value)
{
	gcap *cap_temp = new gcap;
	cap_temp->node1 = this;
	cap_temp->value = value;
	cap_temp->name = name;
	gcap_list.push_back(cap_temp);
}						
void node::add_ccap(string name,double value,node* node1)
{
	ccap *cap_temp = new ccap;
	cap_temp->node1 = this;
	cap_temp->node2 = node1;
	cap_temp->value = value;
	cap_temp->name = name;
	this->ccap_list.push_back(cap_temp);
  	node1->ccap_list.push_back(cap_temp);
}						


