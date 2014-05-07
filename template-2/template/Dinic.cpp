struct Dinic {
	int S,T,delta;
	struct Edge {
		int y,f;
		Edge *r,*next;
		Edge () {}
		Edge (int _y,int _f,Edge *_next) : y(_y), f(_f), next(_next) {} 
	}*h[maxp];
	int d[maxp],q[maxp];
	void init(int _S,int _T) {
		S=_S, T=_T;
		fill(h,0);
	}
	void Add_Edge(int x,int y,int f) {
		h[x]=new Edge(y,f,h[x]),h[y]=new Edge(x,0,h[y]);
		h[x]->r=h[y],h[y]->r=h[x];
	}
	bool Build() {
		fill(d,127);d[S]=0;
		q[0]=S;int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[x]+1<d[y]) {
					d[y]=d[x]+1;
					q[r++]=y;
					if (y==T) return 1;
				}
			}
		}
		return 0;
	}
	bool Find(int x,int now_flow) {
		if (x==T) {
			delta=now_flow;
			return 1;
		}
		ForE(e,x) if (e->f) {
			int y=e->y;
			if (d[x]+1==d[y] && Find(y,min(now_flow,e->f))) {
				e->f-=delta,e->r->f+=delta;
				return 1;
			}
		}
		return 0;
	}
	int MaxFlow() {
		int res=0;
		while (Build()) 
			while (Find(S,inf)) 
				res+=delta;
			
		return res;
	}
};
