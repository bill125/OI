void dfs(int x,int fa) {
	v[x]=1;
	dfn[x]=low[x]=++Index;
	ForE(e,x) {
		int y=e->y;
		if (y!=fa && v[y]==1) low[x]=min(low[x], dfn[y]);
		if (!v[y]) {
			dfs(y, x);
			low[x]=min(low[x], low[y]);
			if (dfn[x]<low[y]) e->bridge=e->r->bridge=1;
		}
	}
	v[x]=2;
}