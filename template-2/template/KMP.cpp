namespace KMP {
	int la,lb;
	int next[maxn];
	void init(char a[],char b[]) {
		la = strlen(a),lb = strlen(b);
		next[0] = -1;
		For(i,1,la-1) {
			int j;
			for (j = next[i-1];j!=-1 && a[i]!=a[j+1];j = next[j]) ;
			if (a[j+1] == a[i]) next[i] = j+1;
			else next[i] = -1;
		}
	}
	int Run(char a[],char b[]) {
		init(a,b);
		int j = -1,ans = 0;
		rep(i,lb) {
			while (j!=-1 && a[j+1] != b[i]) j = next[j];
			if (a[j+1] == b[i]) ++ j;
			if (j == la-1) ++ans,j = next[j];
		}
		return ans;
	}
}
