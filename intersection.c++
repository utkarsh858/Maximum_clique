
Graph intersection(Graph C,Graph T){
	Graph R(C.n);
	for (int i = 1; i < C.n+1; ++i)
	{
		if(C.V[i] && T.V[i]) R.V[i] = true;
	}
	for (int i = 1; i < C.n+1; ++i)
	{
		for (int j = 1; j < C.n+1; ++j)
		{
			if(C.edges[i][j] && T.edges[i][j]) R.edges[i][j] = true;
		}
	}
	return R;
}