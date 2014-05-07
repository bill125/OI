struct Edge {
	int t,c;
	Edge (int _t,int _c) : t(_t), c(_c) {};
};
vector<Edge> E[maxn];

struct State {
	int t,x;
	State() {}
	State(int _t,int _x) : t(_t), x(_x) {}
	inline bool operator <(const State& o) {return x < o.x;}  
};

template <class T>
struct Heap {
	int sz;
	T A[maxe];
	Heap(): sz(0) {} 
	void clear() {
		sz = 0;
	}
	T top() {
		return A[1];
	}
	void up(int x) {
		while (x>1) {
			if (A[x>>1]<A[x]) return ;
			swap(A[x],A[x>>1]);
			x>>=1;
		}
	}
	void down(int x) {
		while ((x<<1) <= sz) {
			int y = ((x<<1)+1 <= sz && A[(x<<1)+1] < A[(x<<1)]) ? (x<<1)+1 : (x<<1);
			if (A[x]<A[y]) return ; 
			swap(A[x],A[y]);
			x = y;
		}
	}
	void push(const T &t) {
		A[++sz] = t;
		up(sz);
	}
	void pop() {
		swap(A[1],A[sz--]);
		down(1);
	}
};
Heap<State> Q;

void Add_Edge(int s,int t,int c) {
	E[s].pb(Edge(t,c));
}

void Dijkstra(const int &x,int d[]) {
	rep(i,n) d[i] = inf;
	d[x] = 0;
	Q.push(State(x,0));
	rep(i,n) {
		State now;
		while (true) {
			now = Q.top();
			Q.pop();
			if (d[now.t] == now.x) break;
		}
		ForE(e,now.t)
			if (d[now.t] + e->c < d[e->t]) {
				d[e->t] = d[now.t] + e->c;
				Q.push(State(e->t,d[e->t]));
			} 	
	}
}
