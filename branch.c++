void initial_branch(int u, Graph<int> G){
	Graph P = G.neighbourhood(u);
	if(P.size() <= H.size()) return;
	Map<int,int> Kn = core_numbers(P);
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
	int L = color(P,Kn);
	if(L <= H.size()) return;
	Graph C;
	branch(P,C);
}

