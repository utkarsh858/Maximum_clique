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
	int L = color(P,Kn);  // what is this color??
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
		if(P_new.size() > 0){
			int L = color(P_new);
			if(c_new + L > H.size()) 
				{
					// making C'
					branch(P_new, C_new);
				}
		}else if(c_new > H.size()){
			H = C_new;
			vector g_vert = G.getVertices();
			for(auto g : g_vert){
				if(K[g] < H.size()) { G.remove(g); break;}
			}
		}
		
	}
}