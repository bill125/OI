struct Edge {
	int to,len,next;
};

namespace SPFA {
	int n,et;
	int h[maxm];
	Edge e[maxe];
	deque<Pair> q;

	void init(const int &_n) { n = _n; fill(h,0); et = 0; }
	void Add_Edge (int x,int y,int z) {
		++et;
		e[et].to = y,e[et].len = z,e[et].next = h[x],h[x] = et;
	}
	void run(int root,int d[]) {
		q.clear();
		rep(i,n) d[i] = inf;d[root] = 0;
		q.pb(mp(root,0));
		while (!q.empty()) {
			while (!q.empty () && q.front().second != d[q.front().first]) 
				q.pop_front();
			if (q.empty()) break;
			int x = q.front().first;
			q.pop_front();
			ForE(i,x) 
				if (d[e[i].to] > d[x] + e[i].len) {
					d[e[i].to] = e[i].len + d[x];
					if (d[e[i].to] <= q.front().second) q.push_front(mp(e[i].to,d[e[i].to]));
					else q.pb(mp(e[i].to,d[e[i].to]));
				}
		}
	}
}