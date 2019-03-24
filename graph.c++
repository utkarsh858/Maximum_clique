
class Graph 
{ 
public: 
	vector<int> V;
  
    // Pointer to an array containing adjacency lists 
    // list<int> *adj;
    map<int,list<int> > adj;


    // function to add an edge to graph 
    void add(int u, int v); 
  	void add(int u);
  	void remove(int u);
  	int size();
  	vector<int> getVertices();
 	Graph neighbourhood(int v);
 	bool edge_exists(int u,int v);
	map<int,int> degrees();
	Graph& operator=(const Graph & p);
	    bool DFSUtil(int, vector<bool> &, vector<int> &, int k);
    list<int> kcores(int k);
    map<int, int> core_numbers(vector<int>);
};

Graph& Graph::operator=(const Graph & p){
	if(this != &p){
		V.resize(p.V.size());
		for(int i=0;i<V.size();i++) V[i]=p.V[i];

		for(map<int,int>::iterator it=adj.begin(); it != adj.end() ;it++) it->second.clear();
		adj.clear();
		for(map<int,int>::iterator it=p.adj.begin(); it != p.adj.end() ;it++) {
			adj[it->first] = *(new list<int>);
			for (std::list<int>::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
			{
				adj[it->first].push_back(*jt);
			}
		}

	}
	return *this;
}

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

void Graph::add(int u)
{
    //adj[u] = *(new list<int>);
    V.push_back(u);
}

void Graph::add(int u, int v)
{
    list<int>::iterator it;
    if ((it = find(adj[u].begin(), adj[u].end(), v)) == adj[u].end())
        adj[u].push_back(v);
    if ((it = find(adj[v].begin(), adj[v].end(), u)) == adj[v].end())
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


bool Graph::DFSUtil(int v, vector<bool> &visited, vector<int> &vDegree, int k)
{
    visited[v] = true;
    //map<int, list<int>>::iterator cur_it;
    //cur_it = find(adj.begin(), adj.end(), v);

    list<int>::iterator i;
    
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (vDegree[v] < k)
            vDegree[*i]--;

        if (!visited[*i])
        {
            if (DFSUtil(*i, visited, vDegree, k))
                vDegree[v]--;
        }
    }

    return (vDegree[v] < k);
}

list<int> Graph::kcores(int k)
{
    vector<bool> visited(V.size(), false);
    vector<bool> processed(V.size(), false);

    int mindeg = INT_MAX;
    int startvertex;

    vector<int> vDegree(V.size());
    //map<int, list<int>>::iterator it = adj.begin();
    for (int i = 0; i < V.size(); i++)
    {
        //vDegree[i] = adj[i].size();
        vDegree[i] = adj[i].size();
        if (vDegree[i] < mindeg)
        {
            mindeg = vDegree[i];
            startvertex = i;
        }
    }

    DFSUtil(startvertex, visited, vDegree, k);

    for (int i = 0; i < V.size(); i++)
        if (visited[i] == false)
            DFSUtil(i, visited, vDegree, k);

    list<int> remaining_vertex;
    for (int v = 0; v < V.size(); v++)
    {
        if (vDegree[v] >= k)
        {
            remaining_vertex.push_back(v);
        }
    }

    return remaining_vertex;
}

map<int, int> Graph::core_numbers()
{
	v = this->V;
    map<int, int> core;
    auto it = v.begin();
    while(it != v.end())
    {
        int k = 2;
        bool flag = true;
        while(flag)
        {
            list<int> rem;
            rem = kcores(k);
            if (find(rem.begin(), rem.end(), *it) == rem.end())
            {
                core[*it] = k-1;
                flag = false;
            }
            k++;
        }
        ++it;
    }

    return core;
}
