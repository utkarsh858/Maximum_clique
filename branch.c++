
void branch(Graph P, Graph C, Graph& G){
	while(P.size()>0 && (P.size() + C.size() > H.size())){
		vector<int> p_vert = P.getVertices();
		int w = p_vert[0];
		P.remove(w);	
		int c_new = C.size() + 1;
		Graph Nw = G.neighbourhood(w);
		Graph P_new = intersection(Nw, P);
		Graph C_new;
		if(P_new.size() > 0){
			int L = P_new.color();
			if(c_new + L > H.size()) 
				{
					C.add(w);
					for(int i=1;i<G.n+1;i++){
						if(G.edge_exists(i,w)) C.add(i,w);
					}

					branch(P_new, C,G);
				}
		}else if(c_new > H.size()){

					C.add(w);
					for(int i=1;i<G.n+1;i++){
						if(G.edge_exists(i,w)) C.add(i,w);
					}

			H = C;
			vector<int> g_vert = G.getVertices();
			K = G.core_numbers();
			for(auto g : g_vert){
				if(K[g] < H.size()) { G.remove(g);
					// removed break;
				}
			}
		}
		
	}
}

void initial_branch(int u, Graph &G){
	Graph P = G.neighbourhood(u);
	if(P.size() <= H.size()) return;
	map<int,int> Kn = P.core_numbers();
	int Kp = INT_MIN;
	for (map<int,int>::iterator it = Kn.begin(); it != Kn.end(); ++it)
	{
		if(Kp < (it->second)) Kp = it->second;
	}
	if(Kp+1 < H.size()) return;
	vector<int> p_vert = P.getVertices();
	for(auto p : p_vert){
		if(Kn[p] < H.size()) {P.remove(p);
			// break;
		}
	}
	int L = P.color(Kn);  // what is this color??
	
	if(L <= H.size()) return;
	Graph C;
	branch(P,C,G);
}
