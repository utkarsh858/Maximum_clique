
class Graph 
{ 
public: 

	vector<int> V;

    map<int,list<int> > adj;
    
    Graph(){}
    Graph(int N){
        V.resize(N);
        for(int i=0;i<N;i++) V[i] = i+1;        
    }
    void resize(int N);
    void add(int u, int v); 
  	void add(int u);
  	void remove(int u);
  	int size();
  	vector<int> getVertices();
 	Graph neighbourhood(int v);
 	bool edge_exists(int u,int v);
	map<int,int> degrees();
	Graph& operator=(const Graph & p);
    bool DFSUtil(int v, map<int, bool> &visited, map<int, int> &vDegree, int k);
    list<int> kcores(int k, vector<int> cur_rem_ver);
    map<int, int> core_numbers();
    int color();
    void colorUtil(map<int,int>& ass_color,int v, map<int,bool> &visited);
    int color(map<int,int> & K);
    void colorKUtil(map<int,int>& ass_color,int v, map<int,bool> &visited);
    void print();

};

void Graph::resize(int N){
    V.resize(N);
    for(int i=0;i<N;i++) V[i] = i+1;
}

void Graph::print(){
    cout << "Vertices are:"<< endl;
    for (int i = 0; i < V.size(); ++i)
    {
        cout << V[i]<<" ";
    }
    cout << endl;
    for (std::map<int,list<int>>::iterator it = adj.begin(); it != adj.end(); ++it)
    {
        cout << it->first<<" - >>> ";
        for (std::list<int>::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
        {
            cout <<" "<< *jt;
        }
        cout << endl;
    }
    cout << endl;
}

Graph& Graph::operator=(const Graph & p){
	if(this != &p){
		V.resize(p.V.size());
		for(int i=0;i<V.size();i++) V[i]=p.V[i];

		for(map<int,list<int>>::iterator it = adj.begin(); it != adj.end() ; it++) it->second.clear();
		adj.clear();
		for(map<int,list<int>>::const_iterator it=p.adj.begin(); it != p.adj.end() ;it++) {
			adj[it->first] = *(new list<int>);
			for (std::list<int>::const_iterator jt = (it->second).begin(); jt != (it->second).end(); ++jt)
			{
				adj[it->first].push_back(*jt);
			}
		}

	}
	return *this;
}

map<int,int> Graph::degrees(){
	std::map<int, int> d;
	map<int,list<int>>::iterator it;
	for(it = adj.begin(); it != adj.end(); it++){
		d[it->first] = (it->second).size() ;
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
        if(it != V.end()){
		V.erase(it);
		adj.erase(u);

		map<int,list<int>>::iterator jt;
		for(jt = adj.begin(); jt != adj.end(); jt++){

			list<int>::iterator kt = find((jt->second).begin(),(jt->second).end(),u);
			
			if(kt != (jt->second).end())
			(jt->second).erase(kt);
		}

        }
	}


void Graph::colorUtil(map<int,int>& ass_color,int v, map<int,bool> &visited)
{
    visited[v] = true;
    for(int n = 1; ;n++){
    	bool found = false;
    	for (list<int>::iterator it = adj[v].begin(); it != adj[v].end() && !found; ++it)
    	{
    		if(ass_color.find(*it) != ass_color.end()){
    			if(ass_color[*it] == n) found = true;
    		}
    	}
    	if(!found) {ass_color[v] = n;break;}
        
    }

    list<int>::iterator i;
    
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {

            colorUtil(ass_color,*i, visited);
        }
    }
}

int Graph::color(){
	map<int,int> m;
	std::map<int,bool> visited;

	colorUtil(m,V[0],visited);
	int maxColor = INT_MIN;
	for (map<int,int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		if((it->second) > maxColor) maxColor = it->second;
	}
	return maxColor;
}

void Graph::colorKUtil(map<int,int>& ass_color,int v, map<int,bool> &visited)
{
    visited[v] = true;
    for(int n = 1; ;n++){
    	bool found = false;
    	for (list<int>::iterator it = adj[v].begin(); it != adj[v].end() && !found; ++it)
    	{
    		if(ass_color.find(*it) != ass_color.end()){
    			if(ass_color[*it] == n) found = true;
    		}
    	}
    	if(!found) {ass_color[v] = n;break;}
      
    }

    list<int> t(adj[v].begin(),adj[v].end());
    list<int>::iterator i;

    // sort(t.begin(),t.end(),decr);
    t.sort(decr);
    for (i = t.begin(); i != t.end(); ++i)
    {
        if (!visited[*i])
        {
            colorKUtil(ass_color,*i, visited);
        }
    }
}

int Graph::color(map<int,int> & K){
	map<int,int> m;
	std::map<int,bool> visited;
    comp_dict = K;
	colorKUtil(m,V[0],visited);
	int maxColor = INT_MIN;
	for (map<int,int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		if((it->second) > maxColor) maxColor = it->second;
	}
	return maxColor;
}

bool Graph::DFSUtil(int v, map<int, bool> &visited, map<int, int> &vDegree, int k)
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

list<int> Graph::kcores(int k, vector<int> cur_rem_ver)
{
    //vector<bool> visited(cur_rem_ver.size(), false);
    //vector<bool> processed(cur_rem_ver.size(), false);

    map<int, bool> visited;
    map<int, bool> processed;
    map<int, int> vDegree;

    for (auto i = cur_rem_ver.begin(); i != cur_rem_ver.end(); i++)
    {
        visited[*i] = false;
        processed[*i] = false;
    }

    int mindeg = INT_MAX;
    int startvertex;

    //vector<int> vDegree(cur_rem_ver.size());
    //map<int, list<int>>::iterator it = adj.begin();
    auto i = cur_rem_ver.begin();
    while( i != cur_rem_ver.end())
    {
        vDegree[*i] = adj[*i].size();
        if (vDegree[*i] < mindeg)
        {
            mindeg = vDegree[*i];
            startvertex = *i;
        }
        ++i;
    }

    DFSUtil(startvertex, visited, vDegree, k);

    for (auto i = cur_rem_ver.begin(); i != cur_rem_ver.end(); i++)
        if (visited[*i] == false)
            DFSUtil(*i, visited, vDegree, k);

    list<int> remaining_vertex;
    for (auto v = cur_rem_ver.begin(); v != cur_rem_ver.end(); v++)
    {
        if (vDegree[*v] >= k)
        {
            remaining_vertex.push_back(*v);
        }
    }

    return remaining_vertex;
}

map<int, int> Graph::core_numbers()
{

    map<int, int> core;
    auto it = V.begin();
    while(it != V.end())
    {
        int k = 2;
        bool flag = true;
        while(flag)
        {
            list<int> rem;
            rem = kcores(k, V);
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