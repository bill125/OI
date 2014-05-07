namespace MST {
	int n;
	int f[maxn],rank[maxn],an[maxn];
	void init(const int & _n) {
		n = _n;
		rep(i,n) f[i] = i,an[i] = i;
		fill(rank,0);
	}
	int find(int x) {
		if (f[x] != x) f[x] = find(f[x]);
		return f[x];
	}
	bool merge(int x,int y) {
		x = find(x),y = find(y);
		if (x == y) return 0;
		an[y] = x;
		if (rank[x] == rank[y]) ++ rank[x];
		if (rank[x] < rank[y]) f[x] = y;
		else f[y] = x;
		return 1;
	}
	int ask(int x) {
		return an[find(x)];
	}
}

namespace LCA {
	struct Tag {
		int o,i;
		Tag (int _o,int _i) : o(_o), i(_i) {}
		Tag () {}
	};
	int n;
	int res[maxt];
	bool v[maxn];
	vector<Tag>	T[maxn];
	vector<int> e[maxn];
	void init(const int & _n) {
		n = _n;
		rep(i,n) T[i].clear(),e[i].clear();
		MST::init(n);
	}
	void Add_Tag(int i,int x,int y) {
		T[x].pb(Tag(y,i));
		T[y].pb(Tag(x,i));
	}
	void Add_Edge(int x,int y) {
		e[x].pb(y);
	}
	void DFS(int x) {
		v[x] = 1;
		forv(i,T[x]) {
			int t = MST::ask(T[x][i].o);
			if (v[t]) res[T[x][i].i] = t;
		}
		forv(i,e[x]) 
			if (!v[e[x][i]]) {
				DFS(e[x][i]);
				MST::merge(x,e[x][i]);
			}
	}
	void work(const int & root,int ans[]) {
		fill(res,0),fill(v,0);
		DFS(root);
		ans = res;
	}
}