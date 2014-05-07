struct Edge {
	int y;
	Edge *next;
	Edge (int _y, Edge* _next) : y(_y), next(_next) {}
}*h[maxn];
int p[maxn][20];
int q[maxn], dep[maxn];
bool v[maxn];

void Add_Edge(int x,int y) {
	h[x]=new Edge(y,h[x]);
}

void PreWork() {
	fill(p,-1);
	int r=1;q[0]=0, dep[0]=0, v[0]=1;
	rep(i,r) {
		int x=q[i];
		ForE(e,x) {
			int y=e->y;
			if (!v[y]) {
				v[y]=1, dep[y]=dep[x]+1;
				p[y][0]=x;
				q[r++]=y;
			}
		}
		For(j,1,19) 
			if (p[x][j-1]!=-1) p[x][j]=p[p[x][j-1]][j-1];
			else break;
	}
}

int lca(int u,int v) {
	if (dep[u]<dep[v]) swap(u,v);
	if (dep[u]!=dep[v]) 
		repD(i,20) if (dep[u]-dep[v]>=(1<<i)) u=p[u][i];
	if (u==v) return u;
	repD(i,20) if (p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
	return p[u][0];
}