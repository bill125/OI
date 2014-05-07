struct CostFlow {
    int S,T,n;
    struct Edge {
        Edge *r,*next;
        int y,c,f;
        Edge () {}
        Edge (Edge *_next, int _y,int _c,int _f) : next(_next), y(_y), c(_c), f(_f) {}
    }*h[maxp],*prev[maxp];
    void init(int _n,int _S,int _T) {
        n=_n, S=_S, T=_T;
        fill(h,0);
    }
    void Add_Edge(int x,int y,int c,int f) {
        Edge *e1=h[x]=new Edge(h[x],y,c,f),*e2=h[y]=new Edge(h[y],x,-c,0);
        e1->r=e2, e2->r=e1;
    }
    int Find() {
        deque<Pair> q;q.clear();
        vector<int> d(n,10000000);
        d[S]=0;q.pb(mp(S,0));
        for (;;) {
            Pair now=mp(0,-1);
            while (!q.empty()) {
                now=q.front();q.pop_front();
                if (now.second==d[now.first]) break;
            }
            int x=now.first;
            if (now.second!=d[x]) break;
            ForE(e,x) if (e->f) {
                int y=e->y;
                if (d[x]+e->c<d[y]) {
                    d[y]=d[x]+e->c;
                    prev[y]=e;
                    if (q.empty() || d[y]<q.front().second) q.push_front(mp(y,d[y]));
                    else q.pb(mp(y,d[y]));
                }
            }
        }
        if (d[T]==10000000) return -1;
        int now_flow=inf;
        for (int x=T; x!=S; x=prev[x]->r->y) mine(now_flow, prev[x]->f);
        for (int x=T; x!=S; x=prev[x]->r->y)
            prev[x]->f-=now_flow, prev[x]->r->f+=now_flow;
        return d[T]*now_flow;
    }
    int MinCostFlow() {
        int res=0;
        for (;;) {
            int t=Find();
            if (t==-1) break;
            res+=t;
        }
        return res;
    }
};
