namespace KM {
	int w[maxn][maxn],n,slack[maxn],lx[maxn],ly[maxn],vx[maxn],vy[maxn],prev[maxn];
	void init(const int _n,const int _w[][maxn]) {
		n = _n;
		rep(i,n) rep(j,n) w[i][j] = _w[i][j];
	}
	bool find(int x) {
		vx[x] = 1;
		rep(y,n) {
			if (vy[y]) continue;
			int t = lx[x] + ly[y] - w[x][y];
			if (t == 0) {
				vy[y] = 1;
				if (prev[y] == -1 || find(prev[y])) {
					prev[y] = x;
					return 1;
				}
			}
			else 
				slack[y] = min(slack[y],t);
		}
		return 0;
	}
	int km() {
		rep(i,n) ly[i] = lx[i] = -inf,prev[i] = -1;
		rep(i,n) rep(j,n) lx[i] = max(lx[i],w[i][j]); 
		rep(x,n) {
			rep(i,n) slack[i] = inf;
			for(;;) {
				fill(vx,0),fill(vy,0);
				if (find(x)) break;
				int d = inf;
				rep(i,n) if (!vy[i]) d = min(d,slack[i]);
				rep(i,n) 
					if (vx[i]) 
						lx[i] -= d;
				rep(i,n)
					if (vy[i])
						ly[i] += d;
					else
						slack[i] -= d;
			}
		}
		int ans = 0;
		rep(i,n) ans += lx[i] + ly[i];
		return ans;
	}
}
