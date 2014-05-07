struct Complex {
	db a, b;
	Complex(db _a=0, db _b=0) : a(_a), b(_b) {}
	friend Complex operator + (const Complex & x, const Complex & y) { return Complex(x.a + y.a, x.b + y.b); }
	friend Complex operator * (const Complex & x, const Complex & y) { return Complex(x.a * y.a - x.b * y.b, x.a * y.b + x.b * y.a); }
	friend Complex operator - (const Complex & x, const Complex & y) { return Complex(x.a - y.a, x.b - y.b); }
};
void FFT(Complex P[], int n, int oper) {
    for (int i = 1, j = 0; i < n - 1; i++) {
		for (int s = n; j ^= s >>= 1, ~j & s;);
		if (i < j) swap(P[i], P[j]);
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = PI / m * oper;
        unit_p0 = Complex(cos(p0), sin(p0));
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}