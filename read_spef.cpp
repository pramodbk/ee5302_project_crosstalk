#include<string>
#include<map>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<fstream>
#include<math.h>
#include"node.hpp"
#include"graph.hpp"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string trim(std::string const& str)
{
    if(str.empty())
        return str;

    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}

void read_spef (graph* graphin) {

string SPEFFile = "1.spef";
ifstream SPEF (SPEFFile.c_str());
if (SPEF.is_open())
  {
    string SPEFLine;
    bool found_dnet = false;
    bool found_conn = false;	
    bool found_cap = false;
    bool found_res = false;	
    while ( getline (SPEF,SPEFLine) )
    {
	// Trim
	SPEFLine.erase(remove(SPEFLine.begin(), SPEFLine.end(), '\n'), SPEFLine.end());
	SPEFLine.erase(remove(SPEFLine.begin(), SPEFLine.end(), '\r'), SPEFLine.end());
	SPEFLine.erase(remove(SPEFLine.begin(), SPEFLine.end(), '\t'), SPEFLine.end());
	SPEFLine = trim(SPEFLine);

	// Ignore null lines
	if ( SPEFLine.empty() ) { continue; }

	vector<string> SPEFTokens = split(SPEFLine, ' ');
	if (SPEFTokens[0] == "*D_NET") { 
		found_dnet = true;
		continue;
	}
	if (SPEFTokens[0] == "*CONN" && found_dnet == true) { 
		found_conn = true;
		continue;
	}
	if (SPEFTokens[0] == "*CAP" && found_dnet == true) { 
		found_cap = true;
		found_conn = false;
		continue;
	}
	if (SPEFTokens[0] == "*RES" && found_dnet == true) { 
		found_res = true;
		found_cap = false;
		continue;
	}
	if (SPEFTokens[0] == "*END") { 
		continue;
	}
	if (found_conn == true) {
		int victim_found=SPEFLine.find("V1"); 					
		if (victim_found!=std::string::npos) {
			graphin->inputs++;
			node *new_node = new node("V1");
			new_node->level = 0;
			new_node->tree_id = 0;
			vector<node*> temp; temp.push_back(new_node);
			graphin->level_order.push_back(temp);
			graphin->node_map["V1"] = new_node;
		}
		int agg_found=SPEFLine.find("A"); 					
		if (agg_found!=std::string::npos) {
			graphin->inputs++;	
			node *new_node = new node("A1");
			new_node->level = 0;
			new_node->tree_id = 1;
			vector<node*> temp; temp.push_back(new_node);
			graphin->level_order.push_back(temp);
			graphin->node_map["A1"] = new_node;
		}
		int out_found=SPEFLine.find("O1"); 					
		if (out_found!=std::string::npos) {
			node *new_node = new node("O1");
			graphin->node_map["O1"] = new_node;
			
		}
	
	}
	if (found_cap == true) {
		if (SPEFTokens.size() == 4) {
			if (graphin->node_map.find(SPEFTokens[1]) == graphin->node_map.end()) {
				node *new_node = new node(SPEFTokens[1]);
				graphin->node_map[SPEFTokens[1]] = new_node;
			}
			if (graphin->node_map.find(SPEFTokens[2]) == graphin->node_map.end()) {
				node *new_node = new node(SPEFTokens[2]);
				graphin->node_map[SPEFTokens[2]] = new_node;
			}
			graphin->add_ccap(SPEFTokens[0],strtod(SPEFTokens[3].c_str(),NULL),graphin->node_map[SPEFTokens[1]],graphin->node_map[SPEFTokens[2]]);
		} else if (SPEFTokens.size() == 3) {
			if (graphin->node_map.find(SPEFTokens[1]) == graphin->node_map.end()) {
				node *new_node = new node(SPEFTokens[1]);
				graphin->node_map[SPEFTokens[1]] = new_node;
			}
			graphin->add_gcap(SPEFTokens[0],strtod(SPEFTokens[2].c_str(),NULL),graphin->node_map[SPEFTokens[1]]);
		} else {
			cout << "Invalid line in SPEF found";
		}
	}
	if (found_res == true) {
		if (SPEFTokens.size() == 4) {
			if (graphin->node_map.find(SPEFTokens[1]) == graphin->node_map.end()) {
				node *new_node = new node(SPEFTokens[1]);
				graphin->node_map[SPEFTokens[1]] = new_node;
			}
			if (graphin->node_map.find(SPEFTokens[2]) == graphin->node_map.end()) {
				node *new_node = new node(SPEFTokens[2]);
				graphin->node_map[SPEFTokens[2]] = new_node;
			}
			graphin->add_res(SPEFTokens[0],strtod(SPEFTokens[3].c_str(),NULL),graphin->node_map[SPEFTokens[1]],graphin->node_map[SPEFTokens[2]]);
		} else {
			cout << "Invalid line in SPEF found "<< SPEFLine<<"\n";
		}
	}
	

    }
  }


}
