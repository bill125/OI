namespace MST {
	int n;
	int f[maxn],rank[maxn];
	void init(const int & _n) {
		n = _n;
		rep(i,n) f[i] = i;
		fill(rank,0);
	}
	int find(int x) {
		if (f[x] != x) f[x] = find(f[x]);
		return f[x];
	}
	bool merge(int x,int y) {
		x = find(x),y = find(y);
		if (x == y) return 0;
		if (rank[x] == rank[y]) ++ rank[x];
		if (rank[x] < rank[y]) f[x] = y;
		else f[y] = x;
		return 1;
	}
}