std::vector<int> comp_dict;

bool decr(int a,int b){
	return (comp_dict[a] > comp_dict[b]);
}

Graph heuristic_clique(Graph G, vetor<int> K){
	int max = 0;
	Graph H;
	
	std::vector<int> V = G.getVertices();
	comp_dict = K;
	sort(V.begin(),V.end(), decr);

	for (int v : V)
	{
		if(K[v] > max){
			
			Graph S = G.neighbourhood(v);
			std::vector<int> s_vert = S.getVertices();
			for(int u : s_vert)
			{
				if(K[u] < max) S.remove(u);
			}

			Graph C;
			
			sort(s_vert.begin(),s_vert.end(),decr);
			for (int u : s_vert)
			{
				// checking whether union makes clique or not
				vector<int> c_vert = C.getVertices();

				bool clique = true;
				for(int j=0; j < c_vert.size() && clique; j++)		
				{
					if(!G.edge_exists(c_vert[j],u)) clique = false;
				}
				if(clique) {
					C.add(u);
					for(int j=0; j < c_vert.size() && clique; j++)		
					{
					if(G.edge_exists(c_vert[j],u)) C.add(u,c_vert[j]);
					}					
				}
			}
			if(C.size() > max) 
				{
					H = C; max = H.size();
				}
		}
	}
	return H;
}