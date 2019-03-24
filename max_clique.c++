Graph max_clique(Graph G){
	vector<int> K = core_numbers(G);
	Graph H = heuristic_clique(G,K);
	// a little doubt in .... where to remove vertices from??
	std::vector<int> V = G.getVertices();
	for(auto v : V){
		if(K[v] < H.size()) G.remove(v);
	}
	// reduced vertices
	V = G.getVertices();
	comp_dict = G.degrees;
	sort(V.begin(),V.end(),incr)
	for(int i=0; i < V.size() && G.size > 0; i++){
		initial_branch(V[i]);
		G.remove(V[i]);
		// periodically what ???
	}

	return H;
}