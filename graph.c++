
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
  	int size();
  	vector<int> getVertices();
 	Graph neighbourhood(int v);
}; 

void Graph::add(int u){
	adj[u] = new list<int>;
}

void Graph::add(int u, int v) 
{ 	
	if(adj[u].find(v) != adj[u].end())
    adj[u].push_back(v); 
	if(adj[v].find(u) != adj[v].end())
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
    			if(adj[u].find(b) != adj[u].end()) R.add(v,b);
    		}
		}

		return R;
	}

	void Graph::remove(int u){
		vector<int>::iterator it = V.find(u);
		V.erase(it);

		adj.erase(u);

		for(auto const& i : adj){
			
		}
	}