// also implement deep copy.(IMPORTANT)
class Graph 
{ 
	vector<int> V;
  
    // Pointer to an array containing adjacency lists 
    // list<int> *adj;
    map<int,list<int> > adj;
public: 

    // function to add an edge to graph 
    void add(int u, int v); 
  	void add(int u);
  	void remove(int u);
  	int size();
  	vector<int> getVertices();
 	Graph neighbourhood(int v);
 	bool edge_exists(int u,int v);
	map<int,int> degrees();
};

map<int,int> degrees(){
	std::map<int, int> d;
	map<int,int>::iterator::it;
	for(it = adj.begin(),it != adj.end(), it++){
		d[it->first] = it->second.size() ;
	}
	return d;
}

bool Graph::edge_exists(int u,int v){
	list<int>::iterator it = find(adj[u].begin(), adj[u].end(), v);
	return (it != adj[u].end());
}

void Graph::add(int u){
	adj[u] = *(new list<int>);
}

void Graph::add(int u, int v) 
{ 	
	list<int>::iterator it;
	if((it = find(adj[u].begin(),adj[u].end(),v )) != adj[u].end())
    adj[u].push_back(v); 
	if((it = find(adj[v].begin(),adj[v].end(),u )) != adj[v].end())
    adj[v].push_back(u); 
} 

int Graph::size(){
	return V.size();
}
  	vector<int> Graph::getVertices(){
  		return V;
  	}


	Graph Graph::neighbourhood(int u){
		Graph R;
		R.add(u);

		for (auto const& v : adj[u]) {
    		R.add(v);

    		R.add(u,v);
    		for(auto const& b : adj[v]){
    			list<int>::iterator it;
    			if((it = find(adj[u].begin(),adj[u].end(),b )) != adj[u].end()) R.add(v,b);
    		}
		}

		return R;
	}

	void Graph::remove(int u){
		vector<int>::iterator it = find(V.begin(),V.end(),u);
		V.erase(it);

		adj.erase(u);

		map<int,list<int>>::iterator jt;
		for(jt = adj.begin(); jt != adj.end(); jt++){

			list<int>::iterator kt = find(jt->second.begin(),jt->second.end(),u);
			
			
			jt->second.erase(kt);
		}
	}