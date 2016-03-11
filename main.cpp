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
#include"read_spef.cpp"

using namespace std;

int main(int argc, char *argv[]) {

//Initialize graph
graph RC;
//Read spef to graph
read_spef(&RC);

//levelize rc tree
RC.levelize();
//calculate moments
// 0th Tree, 1st node
RC.calculate_moments(0,1);

return 0;

}




 
