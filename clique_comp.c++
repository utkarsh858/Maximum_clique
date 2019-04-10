map<int,int> comp_dict;

bool decr(int a,int b){
	return (comp_dict[a] > comp_dict[b]);
}

bool incr(int a,int b){
	return (comp_dict[a] < comp_dict[b]);
}