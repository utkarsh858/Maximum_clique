#include <bits/stdc++.h>

using namespace std;

#include "globals.c++"
#include "clique_comp.c++"
#include "graph.c++"
#include "intersection.c++"
#include "heuristic_clique.c++"
#include "branch.c++"
#include "max_clique.c++"


int main(int argc, char const *argv[])
{

Graph G(26);
G.add(1,5);
G.add(1,22);
G.add(1,6);
G.add(1,7);
G.add(1,23);
G.add(1,8);
G.add(1,24);
G.add(2,5);
G.add(2,6);
G.add(2,7);
G.add(2,8);
G.add(3,5);
G.add(3,6);
G.add(3,7);
G.add(3,8);
G.add(4,5);
G.add(4,6);
G.add(4,7);
G.add(4,8);
G.add(5,9);
G.add(5,15);
G.add(6,17);
G.add(6,23);
G.add(7,14);
G.add(8,23);
G.add(9,10);
G.add(9,11);
G.add(9,12);
G.add(9,13);
G.add(9,14);
G.add(9,15);
G.add(9,16);
G.add(10,11);
G.add(10,26);
G.add(11,13);
G.add(12,13);
G.add(14,15);
G.add(15,23);
G.add(15,17);
G.add(15,21);
G.add(16,17);
G.add(17,18);
G.add(17,19);
G.add(19,20);
G.add(19,21);
G.add(19,22);
G.add(19,24);
G.add(20,21);
G.add(20,22);
G.add(21,22);
G.add(23,24);
G.add(23,25);
G.add(23,26);
G.add(24,25);
G.add(24,26);
G.add(25,26);
Graph C = max_clique(G);
C.print();
	return 0;
}