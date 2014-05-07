namespace Extended_KMP {
	int A[maxn];
	char s[maxn],p[maxn];
	int n,m;
	
	void init(char a[], char b[]) {
		m = strlen(a),n = strlen(b);
		rep(i,m+1) s[i] = a[i];
		rep(i,n+1) p[i] = b[i];
	}
	
	void GetA() {
		A[0] = n,A[1] = n-1;
		rep(i,n) if (p[i]^p[i+1]) {A[1] = i;break;}
		int k = 1;
		For(i,2,n-1) 
			if (i+A[i-k]-1 < k+A[k]-1) A[i] = A[i-k];
			else {
				A[i] = max(0,k+A[k]-i);
				For(j,max(i,k+A[k]),n-1) { 
					if (p[j]^p[j-i]) break;
					A[i] = j-i+1;
				}
				k = i;
			}
	}
	
	void GetB(int B[]) {
		int k = 0;
		B[0] = 0;
		For(i,1,m-1) 
			if (i+A[i-k]-1 < k+B[k]-1) B[i] = B[i-k];
			else {
				B[i] = max(0,k+B[k]-i);
				For(j,max(i,k+B[k]),m-1) {
					if (j-i >= n || (s[j]^p[j-i])) break;
					B[i] = j-i+1;
				}
				k = i;
			} 
	}
	
	void Run(int B[],char a[],char b[]) {
		init(a,b);
		GetA();
		GetB(B);
	}
}

