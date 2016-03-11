#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<fstream>
#include<math.h>
#include"node.hpp"
#include"graph.hpp"
#include"equation.cpp"

void graph::calculate_moments (int tree,int nodename) {  

//first moment
// tree_id ==> victim
// all other tree_id  ==> aggressors
// victim dc voltages are zero
// agrressor dc voltages are one
for ( int tree_id = 0; tree_id < inputs; tree_id++) {
for(size_t i = 0; i < level_order[tree_id].size(); i++){
     if (tree_id == 0) {
	level_order[tree_id][i]->voltage = 0;
	level_order[tree_id][i]->current=0;
     } else {
	level_order[tree_id][i]->voltage = 1;
	level_order[tree_id][i]->current=0;
     }
}
}

vector<double> m;
m.push_back(tree);
for ( int mn = 0; mn < 4; mn++) {
// Higher order moments
for ( int tree_id = 0; tree_id < inputs; tree_id++) {
for(int i = level_order[tree_id].size()-1 ;i>=0 ; i--){
	node* current_node = level_order[tree_id][i];
	current_node->current=0;

	// add currents in present node
	// For all grounded capacitances calculate ground currents 
	for(size_t j = 0; j < current_node->gcap_list.size(); j++){
		// current = C*m , m=voltage moment
		current_node->current += -1*(current_node->voltage)*(current_node->gcap_list[j]->value);
	}
	// For all coupling capacitances calculate currents between the interacting nodes
	for(size_t j = 0; j < current_node->ccap_list.size(); j++){
		// current = C*(m2 - m1) , m=voltage moment
		node* ccap_node = current_node->ccap_list[j]->get_other_node(current_node);
		current_node->current += (ccap_node->voltage - current_node->voltage)*(current_node->ccap_list[j]->value);
	}
	// Cumulate resistive currents in all downstream nodes
	for(size_t j = 0; j < current_node->res_list.size(); j++){
		node* res_node = current_node->res_list[j]->get_other_node(current_node);
		if ( res_node->level > current_node->level) {
		current_node->current += res_node->current;
		}
	}
//	cout << "tree "<<tree_id << " node " << current_node->NodeName << "\tcurrent after all currents:" << current_node->current <<"\n";
}
}
for ( int tree_id = 0; tree_id < inputs; tree_id++) {
// Calculate next moment as the voltage at the node
for(size_t i = 0; i < level_order[tree_id].size(); i++){
	node* current_node = level_order[tree_id][i];
	current_node->voltage=0;

	for(size_t j = 0; j < current_node->res_list.size(); j++){
		node* res_node = current_node->res_list[j]->get_other_node(current_node);
		// next voltage = upstream node voltage + RC 
		if ( res_node->level < current_node->level) {
		current_node->voltage += res_node->voltage + current_node->res_list[j]->value*current_node->current ;
		}
	}
//	cout << "tree "<<tree_id << " node " << current_node->NodeName << "\tVoltage moment:" << current_node->voltage <<"\n";
//	cout << "tree "<<tree_id << " node " << current_node->NodeName << "\tCurrent moment:" << current_node->current <<"\n";
}

}
m.push_back(level_order[tree][nodename]->voltage);
//cout << level_order[tree][nodename]->voltage <<"\n" ;
}


// Calculate reduced 2 pole/1 zero constants from original moments
vector<double> yy = solve_linear (-1,m[0],0,m[1],0,m[1],m[0],m[2],0,m[2],m[1],m[3]);
double a0 = m[0];
double a1 = yy.at(0);
double b1 = yy.at(1);
double b2 = yy.at(2);
//cout << a1 << " " << b1 << " " << b2  << "\n" ;

double pole1 = (b1 + sqrt(b1*b1 - 4*b2) )/(2);
double pole2 = (b1 - sqrt(b1*b1 - 4*b2) )/(2);

//cout << pole1 << " " << pole2 << " \n" ;

// Calculate Partial fraction residues
vector<double> x = solve_linear (pole1*pole2,pole2,pole1,0,1,0,0,-a0,(pole1+pole2),1,1,-a1);
//cout << x.at(0) << " "<< x.at(1) << " " << x.at(2) << " \n" ;
double k1 = x.at(0);
double k2 = x.at(1);
double k3 = x.at(2);


//File with data for plotting
ofstream datafile;
datafile.open ("log.dat");

// Calculate values needed for graph plotting
for (int i=1 ; i<=300; i++) {
double t = 0.1*i;
double y = k1 + k2*exp(-t/pole1)/pole1 + k3*exp(-t/pole2)/pole2; 
y = k1 + k2*exp(-t/pole1)/pole1 + k3*exp(-t/pole2)/pole2; 

datafile << t <<" " << y<< "\n";
}

datafile.close();

}
