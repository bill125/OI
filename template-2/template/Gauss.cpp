	rep(i,n) {
		int j = i;
		while (j < n && 0==a[j][i]) ++j;
		if (j == n) continue;
		rep(k,n+1) swap(a[i][k],a[j][k]);
		For(k,i+1,n-1) {
			db t = a[k][i]/a[i][i];
			For(j,i,n) a[k][j] -= t*a[i][j];
		}
	}
	
	repD(i,n) {
		For(j,i+1,n-1) a[i][n] -= a[i][j]*a[j][n];
		a[i][n] /= a[i][i];
	}
	
