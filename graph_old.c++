
class Graph
{
	std::vector<int> vertices;
	std::vector<pair<int,int>> edges;
public:

	void add(int a){
		vector<int>::iterator it = find(vertices.begin(),vertices.end(),a);
		if(it == vertices.end())
			vertices.insert(a);
	}

	void add(int a, int b){
		bool found = false;
		for(int i=0;i < edges.size() && !found; i++){
			if(edges[i].first == a && edges[i].second == b) found = true;
			if(edges[i].first == b && edges[i].second == a) found = true;
		}
		if(!found)
			edges.insert(make_pair(a,b));
	}

	int size(){
		return vertices.size();
	}

	void remove(int a){
		vector<int>::iterator it = find(vertices.begin(),vertices.end(),a);
		vertices.erase(it);

		int i=0;
		while(i < edges.size()){
			bool found = false;
			if(edges[i].first == a || edges[i].second == a) found = true;

			if(found)
				edges.erase(edges.begin()+i);
			else
				i++;
		}

	}

	std::vector<int> getVertices(){
		return vertices;
	}

	Graph neighbourhood(int v){
		Graph R;
		R.add(v);
		for(int i=0;i<edges.size();i++){
			if(edges[i].first == v) {
				R.add(edges[i].second);
				R.add(edges[i].first,edges[i].second);
			}
			if(edges[i].second == v){
				R.add(edges[i].first);
				R.add(edges[i].second,edges[i].first);

			}
		}

		return R;
	}
};
