namespace SCC {
	const int MAXN = ;
	
	int N, M, T;
	vector<int> G [MAXN];
	int Tick [MAXN], Low [MAXN], Belong [MAXN];
	stack<int> S;
	
	inline void Add (int u, int v) {
		G [u].PB (v);
	}
	
	inline void DFS (int u) {
		S.push (u), Tick [u] = Low [u] = ++T;
		
		for (int i = 0; i < size (G [u]); ++i) {
			int v = G [u][i];
			
			if (!Tick [v]) {
				DFS (v);
				Low [u] = min (Low [u], Low [v]); 
			} else if (!Belong [v])
				Low [u] = min (Low [u], Tick [v]);
		}
		
		if (Low [u] == Tick [u]) {
			M++;
			while (true) {
				int v = S.top (); S.pop ();
				Belong [v] = M;
				if (u == v)
					break;
			}
		}
	}
	
	inline void Get () {
		T = M = 0;
		for (int i = 1; i <= N; ++i)
			Tick [i] = Low [i] = Belong [i] = 0;
		
		for (int i = 1; i <= N; ++i)
			if (!Belong [i])
				DFS (i);
	}
	
	inline int Build (vector<int> F [], vector<int> V []) {
		for (int i = 1; i <= M; ++i) {
			i[F].clear ();
			V [i].clear ();
		}
		
		for (int u = 1; u <= N; ++u)
			for (int i = 0; i < size (G [u]); ++i) {
				int v = G [u][i];
				
				if (Belong [u] != Belong [v])
					F [Belong [u]].PB (Belong [v]);
			}
		
		for (int i = 1; i <= M; ++i) {
			sort (all (F [i]));
			F [i].erase (unique (all (F [i])), F [i].end ());
		}
		
		for (int i = 1; i <= N; ++i)
			V [Belong [i]].PB (i);
		
		return M;
	}
	
	inline void Clear () {
		for (int i = 1; i <= N; ++i)
			G [i].clear ();
	}
}

