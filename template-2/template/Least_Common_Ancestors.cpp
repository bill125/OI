namespace BCJ {
	int n;
	int rank[maxn],f[maxn],an[maxn];
	void init (int _n) {
		n  = _n;
		fill(f,0),fill(an,0),fill(rank,0);
		rep(i,n) f[i] = an[i] = i;
	}
	int getf(int x) {
		if (f[x] != x) f[x] = getf(f[x]);
		return f[x];
	}
	void merge(int x,int y) {
		x = getf(x),y = getf(y);
		if (x == y) return;
		an[y] = an[x];
		if (rank[x] == rank[y]) ++ rank[x];
		if (rank[x] < rank[y]) f[x] = y;
		else f[y] = x;
	}
	int Ask(int x) {
		return an[getf(x)];
	}
}

namespace LCA {
	int n,m,root;
	vector<int> e[maxn];
	bool v[maxn];
	int ans[maxn];
	struct Tag {
		int b,i;
		Tag(int _b,int _i) : b(_b),i(_i) {}
	};
	vector<Tag> t[maxn];
	void init(const int & _n,const vector<int> _e[],int _root) {
		n = _n,m = 0,root = _root;
		rep(i,n) e[i] = _e[i],t[i].clear();
		fill(v,0);
	}

	void Add_Tag(int a,int b) {
		t[a].pb(Tag(b,m)),t[b].pb(Tag(a,m++));
	}
	void DFS(int x) {
		v[x] = 1;
		ForV(i,t[x]) {
			int f = BCJ::Ask(t[x][i].b);
			if (v[f]) ans[t[x][i].i] = f;
		}
		ForV(i,e[x]) {
			if (v[e[x][i]]) continue;
			DFS(e[x][i]);
			BCJ::merge(x,e[x][i]);
		}

	}
	vector<int> Run() {
		BCJ::init(n);
		
		DFS(root);
		
		vector<int> res;res.clear();
		rep(i,m) res.pb(ans[i]+1);
		return res;
	}
}
