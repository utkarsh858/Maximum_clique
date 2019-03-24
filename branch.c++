Graph Intersection(Graph G, Graph V){
	std::vector<int> g = G.getVertices();
	std::vector<int> v = V.getVertices();
	sort(g.begin(),g.end());
	sort(v.begin(),v.end());
	vector<int> common;
	int i=0;int j=0;
	while(i<g.size() || j<v.size()){
		if(i>=g.size() && j>=v.size()) {
			break;
		}
		if(v[j] == g[i]) {
			common.push_back(v[j]);
			j++;i++;
		}else
		if(v[j] > g[i]) i++;
		else j++;
	}

	
}

void initial_branch(int u, Graph<int> &G){
	Graph P = G.neighbourhood(u);
	if(P.size() <= H.size()) return;
	Map<int,int> Kn = P.core_numbers();
	int Kp = INT_MIN;
	for (map<int,int>::iterator it = Kn.begin(); it != Kn.end(); ++it)
	{
		if(Kp < it->second) Kp = it->second;
	}
	if(Kp+1 < H.size()) return;
	vector<int> p_vert = P.getVertices();
	for(auto p : p_vert){
		if(Kn[p] < H.size()) P.remove(p);
	}
	int L = P.color(Kn);  // what is this color??
	if(L <= H.size()) return;
	Graph C;
	branch(P,C,G);
}

void branch(Graph P, Graph C, Graph& G){
	while(P.size() && (P.size() + C.size() > H.size())){
		vector<int> p_vert = P.getVertices();
		int w = p_vert[0];
		int c_new = C.size() + 1;
		Graph Nw = G.neighbourhood(w);
		Graph P_new = Intersection(Nw, P);
		Graph C_new;
		if(P_new.size() > 0){
			int L = P_new.color;
			if(c_new + L > H.size()) 
				{
					// making C'
					C_new = C;
					C_new.add(w);
					std::vector<int> c_vert=C_new.getVertices();
					for(int j=0; j < c_vert.size(); j++)		
					{
						if(G.edge_exists(c_vert[j],u)) C.add(u,c_vert[j]);
					}		


					branch(P_new, C_new);
				}
		}else if(c_new > H.size()){
			C_new = C;
			C_new.add(w);
			std::vector<int> c_vert=C_new.getVertices();
			for(int j=0; j < c_vert.size(); j++)		
			{
				if(G.edge_exists(c_vert[j],u)) C.add(u,c_vert[j]);
			}		

			H = C_new;
			vector g_vert = G.getVertices();
			for(auto g : g_vert){
				if(K[g] < H.size()) { G.remove(g); break;}
			}
		}
		
	}
}