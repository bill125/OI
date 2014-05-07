struct CostFlow {
	int n,s,t,delta;
	deque<Pair> q;
	int d[maxp];
	Edge *h[maxp], mem[maxe], *C, *prev[maxp];
	Edge *makeedge(int x,int y,int f,int c) {
		C->y=y, C->next=h[x], C->f=f, C->c=c;
		return C++;
	}
	void Add_Edge(int x,int y,int f,int c) {
		Edge *e1=h[x]=makeedge(x,y,f,c), *e2=h[y]=makeedge(y,x,0,-c);
		e1->r=e2, e2->r=e1;
	}
	void init(int _s,int _t,int _n) {
		s=_s, t=_t, n=_n;
		fill(h,0), C=mem;
	}
	bool Find() {
		fill(d,-1);
		q.clear(), q.pb(mp(s,0)), d[s]=0;
		while (!q.empty()) {
			Pair tmp=q.front();
			q.pop_front();
			if (d[tmp.first]!=tmp.second) continue;
			int x=tmp.first;
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[x]+e->c<d[y] || d[y]==-1) {
					d[y]=d[x]+e->c;
					prev[y]=e;
					if (q.empty() || d[y]<q.front().second) q.push_front(mp(y,d[y]));
					else q.push_back(mp(y,d[y]));
				}
			}
		}
		if (d[t]==-1) return 0;
		delta=inf;
		for (int x=t; x!=s; x=prev[x]->r->y) delta=min(delta,prev[x]->f);
		for (int x=t; x!=s; x=prev[x]->r->y) prev[x]->f-=delta, prev[x]->r->f+=delta;
		delta*=d[t];
		return 1;
	}
	int Run() {
		int ans=0;
		while (Find())
			ans+=delta;
		return ans;
	}
}A;