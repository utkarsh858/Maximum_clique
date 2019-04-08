Graph intersection(Graph G, Graph V){
	std::vector<int> g = G.getVertices();
	std::vector<int> v = V.getVertices();
	sort(g.begin(),g.end());
	sort(v.begin(),v.end());
	vector<int> common;
	int i=0;int j=0;
	while(i<g.size() && j<v.size()){
		// if(i>=g.size() && j>=v.size()) {
		// 	break;
		// }
		if(v[j] == g[i]) {
			common.push_back(v[j]);
			j++;i++;
		}else
		if(v[j] > g[i]) i++;
		else j++;
	}
	Graph I;
	I.V = common;
	for(int i=0;i<common.size();i++){
	
		for (list<int>::iterator it = G.adj[i].begin(); it != G.adj[i].end(); ++it)
		{
			bool matched = false;
			for (list<int>::iterator jt = V.adj[i].begin();!matched && jt != V.adj[i].end(); ++jt)
			{
				if(*it == *jt) matched = true;
			}
			if(matched) I.add(i,*it);
		}
	}

	return I;
}