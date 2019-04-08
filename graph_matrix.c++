
class Graph 
{ 
public: 

	// vector<int> V;
    int n;
    int count = 0;
    bool* V;
    bool** edges;
    // map<int,list<int> > adj;
    Graph(){

    }
    Graph(int N){
        // V.resize(N);
        n=N; count = n;
        V = new bool[N+1];
        for(int i=0;i<N+1;i++) V[i] = true;
        // for(int i=0;i<N;i++) V[i] = i+1;   
        edges = new bool*[N+1];
        for (int i = 0; i < N+1; ++i)
             {
                 edges[i] = new bool[N+1];
             }
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

void print(){
    cout << "Vertices\n";
    for (int i = 0; i < n+1; ++i)
    {
        if(this->V[i]) cout << i <<" ";
    }
    cout << endl << "Edges";
    for(int i=0;i<n+1;i++){
        if(V[i]){
            cout << i<<" :";
            for (int j = 0; j < n+1; ++j)
            {
                if(edges[i][j]) cout <<" "<<j;
            }
            cout <<endl;
        }
    }
    cout << "---------\n";
}

Graph& operator=(const Graph& p){
    if(this!=&p){
        this->n = p.n;
        V=new int[n+1];
        for (int i = 0; i < n+1; ++i)
        {
            this->V[i] = p.V[i];
        }
        this->edges = new int*[this->n+1];
        for(int i=0;i<n+1;i++) 
            {
                edges[i] = new int[this->n+1];
                for (int j = 0; j < n+1; ++j)
                {
                    this->edges[i][j] = p.edges[i][j];
                }
            }
    }
    return *this;
}

map<int,int> degrees(){
    map<int,int> m;
    for(int i =0;i<n+1;i++) {
        if(V[i]){
            int count=0;
            for(int j=1;j<n+1;j++) if(edges[i][j]) count++;
            m[i]=count;
        }
    }
    return m;
}

bool edge_exists(int u,int v){
    return edges[u][v];
}
void Graph::resize(int N){
        n=N; count = n;
        V = new bool[N+1];
        for(int i=0;i<N+1;i++) V[i] = true;
        edges = new bool*[N+1];
        for (int i = 0; i < N+1; ++i)
             {
                 edges[i] = new bool[N+1];
                 for(int j=0;j<N+1;j++) edges[i][j] = 0;
             }
}

void Graph::add(int u,int v){
    edges[u][v] = true;
}

void Graph::add(int u){
    V[u] = true; count++;
}

void Graph::remove(int u){
    V[u] = false; count--;
    for(int i=0;i<n+1;i++){
        edges[u][i] = false;
        edges[i][u] = false;
    }
}

int Graph::size(){
    return count;
}

vector<int> Graph::getVertices(){
    std::vector<int> r(count);
    int j=0;
    for (int i = 1; i < n+1; ++i)
    {
        if(V[i]) {r[j]=i;j++;}
    }
    return r;
}

Graph neighbourhood(int v){
    Graph r;
    r.n=this->n;
    V = new bool[n+1];
    V[v]= true; int count = 1;
    for(int i=0;i<n+1;i++) V[i]=false;
    r.edges= new bool*[n+1];
    for(int i=0;i<n+1;i++) {
        r.edges[i] = new bool[n+1];
        for(int j=0;j<n+1;j++) r.edges[i][j]=false;
    }
    for(int i=0;i<n+1;i++) if(edges[i][v]) {V[i]=true;count++;r.edges[i][v]=true;r.edges[v][i]=true;}
        r.count = count;
    return r;
}