
class Graph 
{ 
public: 

    int n;
    int count = 0;
    bool* V;
    bool** edges;
    Graph(){

    }
    Graph(int N){
        n=N; count = 0;
        V = new bool[N+1];
        for(int i=1;i<N+1;i++) V[i] = false;

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
    bool DFSUtil(int v, vector<bool> &visited, vector<int> &vDegree, int k);
    // bool DFSUtil(int v, map<int, bool> &visited, map<int, int> &vDegree, int k);
    // list<int> kcores(int k, vector<int> cur_rem_ver);
    vector<bool> kcores(int k);
    map<int, int> core_numbers();

    int color();
    void colorUtil(int m[],int v, bool visited[]);
    int color(map<int,int> & K);
    void colorKUtil(int m[],int v, bool visited[]);
   
    void print();

};

bool Graph::DFSUtil(int v, vector<bool> &visited, vector<int> &vDegree, int k)
{
    visited[v] = true;
    for(int i=0;i< n+1;i++){
        if(edges[v][i]){
            if(vDegree[v] < k)
                vDegree[i]--;
            if(!visited[i]){
                if(DFSUtil(i,visited,vDegree,k)) vDegree[v]--;
            }
        }
    }
    return (vDegree[v]<k);
}
vector<bool> Graph::kcores(int k){
    vector<bool> visited(n+1, false);
    bool processed[n+1];
    vector<int> vDegree(n+1);

    for(int v=0;v<n+1;v++){
        visited[v] = false;
        processed[v] = false;
    }
    int mindeg = INT_MAX;
    int startvertex;

    for(int v=0;v<n+1;v++){
        int count = 0;
        for (int i = 0; i < n+1; ++i)
        {
            if(edges[v][i]) count++;
        }
        vDegree[v] = count;
        if(vDegree[v] < mindeg){
            mindeg = vDegree[v];
            startvertex = v;
        }

    }
    DFSUtil(startvertex, visited, vDegree, k);
    // for(auto v : V){
    for(int v=1;v<n+1;v++){
        if(!visited[v]) DFSUtil(v,visited,vDegree, k);
    }
    std::vector<bool> rem(n,false);
    // for(auto v : V){
    for(int v=1;v<n+1;v++){
        if(vDegree[v] >= k){
            rem[v] = true;
        }
    }
    return rem;
}

map<int,int> Graph::core_numbers(){
    map<int,int> core;
    for (int s=1;s<n+1;s++)
    {
        int k =2;
        bool flag = true;
        while(flag){
            vector<bool> rem;
            rem = kcores(k);
            if(rem[s]){
                core[s] = k-1;
                flag = false;
            }
            k++;
        }
    }
    return core;
}

void Graph::colorUtil(int m[],int v, bool visited[]){
    visited[v] = true;
    for (int i = 0;; ++i)
    {
        bool found = false;
        for (int j = 1; j < n+1 && !found; ++j)
        {
            if(edges[v][j]){ // for adjoint vertices
                if(m[j] && m[j]==n){ // if assigned color
                    found = true;
                }
            }
        }
        if(!found) {m[v] = i; break;}
    }
    for (int i = 1; i < n+1; ++i)
    {
        if(edges[v][i] && !visited[i]){
            colorUtil(m,i,visited);
        }
    }

}

int Graph::color(){
    bool visited[n+1];
    int m[n+1];
    for (int i = 0; i < n+1; ++i)
    {
        m[i] =0;
    }
    int start_vertex;
    for (int i = 0; i < n+1; ++i)
    {
        if(V[i]) {start_vertex = i; break;}
    }
    colorUtil(m,start_vertex,visited);

    int maxColor = INT_MIN;
    for (int i = 0; i < n+1; ++i)
    {
        if(maxColor < m[i]) maxColor = m[i];
    }
    return maxColor;
}

void Graph::colorKUtil(int m[],int v, bool visited[]){
    visited[v] = true;
    for (int i = 0;; ++i)
    {
        bool found = false;
        for (int j = 1; j < n+1 && !found; ++j)
        {
            if(edges[v][j]){ // for adjoint vertices
                if(m[j] && m[j]==n){ // if assigned color
                    found = true;
                }
            }
        }
        if(!found) {m[v] = i; break;}
    }
    vector<int> sorted_vertices(count);
    int p=0;
    for (int i = 1; i < n+1; ++i)
    {
        if(edges[v][i]){
            sorted_vertices[p] = i; p++;
        }
    }
    sort(sorted_vertices.begin(),sorted_vertices.end(),decr);
    for (auto g : sorted_vertices)
    {
        if(!visited[g]){
            colorKUtil(m,g,visited);
        }
    }

}


int Graph::color(map<int,int > & K){
    bool visited[n+1];
    int m[n+1];
    comp_dict = K;
    for (int i = 0; i < n+1; ++i)
    {
        m[i] =0;
    }
    int start_vertex;
    for (int i = 0; i < n+1; ++i)
    {
        if(V[i]) {start_vertex = i; break;}
    }
    colorKUtil(m,start_vertex,visited);

    int maxColor = INT_MIN;
    for (int i = 0; i < n+1; ++i)
    {
        if(maxColor < m[i]) maxColor = m[i];
    }
    return maxColor;
}


void Graph::print(){
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

Graph& Graph::operator=(const Graph& p){
    if(this!=&p){
        this->n = p.n;
        V=new bool[n+1];
        for (int i = 0; i < n+1; ++i)
        {
            this->V[i] = p.V[i];
        }
        this->edges = new bool*[this->n+1];
        for(int i=0;i<n+1;i++) 
            {
                edges[i] = new bool[this->n+1];
                for (int j = 0; j < n+1; ++j)
                {
                    this->edges[i][j] = p.edges[i][j];
                }
            }
    }
    return *this;
}

map<int,int> Graph::degrees(){
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

bool Graph::edge_exists(int u,int v){
    return edges[u][v];
}
void Graph::resize(int N){
        n=N; count = 0;
        V = new bool[N+1];
        for(int i=0;i<N+1;i++) V[i] = false;
        edges = new bool*[N+1];
        for (int i = 0; i < N+1; ++i)
             {
                 edges[i] = new bool[N+1];
                 for(int j=0;j<N+1;j++) edges[i][j] = 0;
             }
}

void Graph::add(int u,int v){
    edges[u][v] = true;
    edges[v][u] = true;
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

Graph Graph::neighbourhood(int v){
    Graph r;
    r.n=this->n;
    r.V = new bool[n+1];
    for(int i=0;i<n+1;i++) r.V[i]=false;

    r.V[v]= true; r.count = 1;
    r.edges= new bool*[n+1];
    for(int i=0;i<n+1;i++) {
        r.edges[i] = new bool[n+1];
        for(int j=0;j<n+1;j++) r.edges[i][j]=false;
    }
    for(int i=0;i<n+1;i++) if(edges[i][v]) {r.V[i]=true;r.count++;r.edges[i][v]=true;r.edges[v][i]=true;}
    
    return r;
}