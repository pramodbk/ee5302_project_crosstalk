#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<ctype.h>
#include<sstream>
#include<iostream>
#include"node.hpp"
#include"graph.hpp"

using namespace std;

graph::graph()  
{
	inputs=0;
};   						// constructor

void graph::add_res(string name,double value,node* node1,node* node2)
{
node2->add_res(name,value,node1);
}						// add input

void graph::add_gcap(string name,double value,node* node1)
{
node1->add_gcap(name,value);
}						// add input

void graph::add_ccap(string name,double value,node* node1,node* node2)
{
node2->add_ccap(name,value,node1);
}						// add input


void graph::levelize() {
queue<node*> to_levelize;
for (map<string,node*>::iterator it=node_map.begin() ; it!=node_map.end(); ++it) {
                if (it->second->level == 0) { 
                        to_levelize.push(it->second);
                }
}
        // Start with all primary inputs

while ( !to_levelize.empty() ) { 
                node* current_node = to_levelize.front();
                to_levelize.pop();
                        

		for(size_t j = 0; j < current_node->res_list.size(); j++){
		node* res_node = current_node->res_list[j]->get_other_node(current_node);
		if ( res_node->level == -1) {
		//cout << "Node " << current_node->NodeName << " has tree_id " << level_order.capacity() <<current_node->tree_id << "\n"; 
                	to_levelize.push(res_node);
			res_node->level = current_node->level+1;
			res_node->tree_id = current_node->tree_id;
			level_order[res_node->tree_id].push_back(res_node);
			//cout << "Assigning level " << res_node->level << " to node " << res_node->NodeName << "\n"; 
                }
		}
}
//for (int i=0; i<level_order[0].size(); i++) { 
//      cout << "\t" << level_order[0][i]->NodeName << "\n" <<endl;
//}
}

