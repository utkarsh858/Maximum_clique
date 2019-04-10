
Graph heuristic_clique(Graph& G, map<int,int> K){
	int max = 0;
	Graph H(G.n);
	
	std::vector<int> V = G.getVertices();
	comp_dict = K;
	sort(V.begin(),V.end(), decr);
	for (int i = 0; i < V.size(); ++i)
	{
		cout << V[i]<<" "<<endl;
	}
	for (int v : V)
	{
		if(K[v] > max){
			
			Graph S = G.neighbourhood(v);
			std::vector<int> s_vert = S.getVertices();
			for(int u : s_vert)
			{
				if(K[u] < max) S.remove(u);
			}
			cout << G.n<<"POP"<<endl;
			Graph C(G.n);
			// for(int i=1;i<=G.n;i++) C.add(i);
			
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