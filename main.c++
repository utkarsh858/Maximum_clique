// #include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

#include "clique_comp.c++"
#include "graph_matrix.c++"
#include "globals.c++"
#include "intersection.c++"
#include "heuristic_clique.c++"
#include "branch.c++"
#include "max_clique.c++"

int main(int argc, char const *argv[])
{
	Graph G;

	fstream data_file;
	if(argc < 2) {
		cout << "Usage : ./a.out [FILENAME]"; exit(0);
	}
	data_file.open(argv[1]);
	char x;
	string temp;
	int a; int b;
	while(data_file >> x){
		if(x=='c') {
			getline(data_file, temp);
		} else if(x=='p') {
			data_file >> temp;
			data_file >> a;
			data_file >> b;
			G.resize(a+1);
			for (int i = 1; i <= a; ++i)
			{
				G.add(i);
			}
		} else if(x=='e'){
			data_file >> a;
			data_file >> b;
			G.add(a,b);
		}
	}
	data_file.close();

	Graph C = max_clique(G);
	cout << "Result Clique C is :: \n";

	C.print();
	return 0;
}
