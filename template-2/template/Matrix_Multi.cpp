struct Matrix {
    int n,m;
    ll a[maxl][maxl];
    Matrix () {}
    Matrix(int _n,int _m) {
		n = _n,m = _m;
		fill(a,0);
	}     
    Matrix operator* (const Matrix &B) {
        Matrix tmp;
        fill(tmp.a,0);
        rep(i,n) rep(j,B.m) 
            rep(k,m) tmp.a[i][j] = tmp.a[i][j] + a[i][k] * B.a[k][j];
        tmp.n = n,tmp.m = B.m;
        return tmp;
    }
    void debug() {
        printf("%d %d\n", n, m);
        rep(i,n) {
            rep(j,m) cout << a[i][j] << " ";
            puts("");
        }
        puts("==================");
    }
    void Unit(int Size) {
		fill(a,0);
		n = m = Size;
		rep(i,Size) a[i][i] = 1;
	};
	Matrix Pow(ll);
}G,S;
 
Matrix Matrix::Pow(ll t) {
    Matrix res;res.Unit(n);

    Matrix A;A = *this;
    while (t) {
        if (t&1) res = res * A;
        A = A * A;
        t >>= 1;
    }
    return res;
}
