Graph max_clique(Graph G){
	cout << "Given Graph G is :: \n";
	G.print();
	// for (list<int>::iterator it = G.adj[0].begin(); it != G.adj[0].end(); ++it)
	// {
	// 	cout << " " <<*it;
	// }
	K = G.core_numbers();
	
	H = heuristic_clique(G,K);
	// a little doubt in .... where to remove vertices from??
	cout << "Heuristic Clique H is :: \n";
	H.print();
	std::vector<int> V = G.getVertices();
	for(auto v : V){
		if(K[v] < H.size()) G.remove(v);
	}
	cout << "Graph G with basic pruning from core_numbers : \n";
	G.print();
	// reduced vertices
	
	while(G.size() > 0){
		V = G.getVertices();
	comp_dict = G.degrees();
		sort(V.begin(),V.end(),incr);
		initial_branch(V[0],G);
		G.remove(V[0]);
		// periodically what ???
	}
	
	return H;
}