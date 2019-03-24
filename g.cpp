#include <bits/stdc++.h>

using namespace std;

class Graph
{
  public:
    vector<int> V;

    // Pointer to an array containing adjacency lists
    // list<int> *adj;
    map<int, list<int>> adj;

  
    // function to add an edge to graph
    void add(int u, int v);
    void add(int u);
    void remove(int u);
    int size();
    vector<int> getVertices();
    Graph neighbourhood(int v);
    bool edge_exists(int u, int v);
    bool DFSUtil(int, vector<bool> &, vector<int> &, int k);
    list<int> kcores(int k);
    map<int, int> core_numbers(vector<int>);
};

bool Graph::edge_exists(int u, int v)
{
    list<int>::iterator it = find(adj[u].begin(), adj[u].end(), v);
    return (it != adj[u].end());
}

void Graph::add(int u)
{
    adj[u] = *(new list<int>);
}

void Graph::add(int u, int v)
{
    list<int>::iterator it;
    //if ((it = find(adj[u].begin(), adj[u].end(), v)) != adj[u].end())
        adj[u].push_back(v);
    //if ((it = find(adj[v].begin(), adj[v].end(), u)) != adj[v].end())
        adj[v].push_back(u);
}

int Graph::size()
{
    return V.size();
}

vector<int> Graph::getVertices()
{
    return V;
}

Graph Graph::neighbourhood(int u)
{
    Graph R;
    R.add(u);

    for (auto const &v : adj[u])
    {
        R.add(v);

        R.add(u, v);
        for (auto const &b : adj[v])
        {
            list<int>::iterator it;
            if ((it = find(adj[u].begin(), adj[u].end(), b)) != adj[u].end())
                R.add(v, b);
        }
    }

    return R;
}

void Graph::remove(int u)
{
    vector<int>::iterator it = find(V.begin(), V.end(), u);
    V.erase(it);

    adj.erase(u);

    map<int, list<int>>::iterator jt;
    for (jt = adj.begin(); jt != adj.end(); jt++)
    {

        list<int>::iterator kt = find(jt->second.begin(), jt->second.end(), u);

        jt->second.erase(kt);
    }
}

bool Graph::DFSUtil(int v, vector<bool> &visited, vector<int> &vDegree, int k)
{
    visited[v] = true;
    map<int, list<int>>::iterator cur_it;
    cur_it = find(adj.begin(), adj.end(), v);

    list<int>::iterator i;
    
    for (i = cur_it->second.begin(); i != cur_it->second.end(); ++i)
    {
        cout<<"Yes\n";
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
    map<int, list<int>>::iterator it = adj.begin();
    for (int i = it->first; i < V.size(); it++)
    {
        //vDegree[i] = adj[i].size();
        vDegree[i] = it->second.size();
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

map<int, int> Graph::core_numbers(vector<int> v)
{
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
        it++;
    }
    return core;
}

int main()
{
    Graph g1;
    /*g1.add(0);
    g1.add(1);
    g1.add(2);
    g1.add(3);
    g1.add(4);
    g1.add(5);
    g1.add(6);
    g1.add(7);
    g1.add(8);*/
    g1.add(0, 1);
    g1.add(0, 2);
    g1.add(1, 2);
    g1.add(1, 5);
    g1.add(2, 3);
    g1.add(2, 4);
    g1.add(2, 5);
    g1.add(2, 6);
    g1.add(3, 4);
    g1.add(3, 6);
    g1.add(3, 7);
    g1.add(4, 6);
    g1.add(4, 7);
    g1.add(5, 6);
    g1.add(5, 8);
    g1.add(6, 7);
    g1.add(6, 8);

    cout<<g1.edge_exists(1,5)<<endl;
    cout << g1.edge_exists(1, 4);

    map<int, int> c = g1.core_numbers(g1.V);
    map<int, int>::iterator it = c.begin();
    while(it != c.end())
    {
        cout<<it->first<<" : "<<it->second<<endl;
        it++;
    }

    return 0;
}