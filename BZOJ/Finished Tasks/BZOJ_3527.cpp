// Author: bill125
// ntr jcpwfloi
// orz LXLWDGY WJMZBMR dilutedream sevenkplus 
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> Pair;
#define rep(i,n) for (int i=0; i<n; ++i)
#define repD(i,n) for (int i=n-1; i>=0; --i)
#define For(i,a,b) for (int i=a; i<=b; ++i)
#define ForD(i,a,b) for (int i=a; i>=b; --i)
#define ForE(i,a) for (Edge* i=h[a]; i; i=i->next)
#define forv(i,a) for (unsigned int i=0, ___t=a.size(); i<___t; ++i)
#define ForV(i,a) for (__typeof(a.begin()) i = a.begin();i != a.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(a) ((a) & (-(a)))
#define sqr(a) ((a)*(a))
#define pb push_back
#define mp make_pair
#define gi gI()
#define cut puts("===================")
 
void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in=NAME+".in", out=NAME+".out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, N = 1<<18;
const db PI = acos(-1.);
int n;
struct Complex {
	db a, b;
	Complex(db _a=0, db _b=0) : a(_a), b(_b) {}
	friend Complex operator + (const Complex & x, const Complex & y) { return Complex(x.a + y.a, x.b + y.b); }
	friend Complex operator * (const Complex & x, const Complex & y) { return Complex(x.a * y.a - x.b * y.b, x.a * y.b + x.b * y.a); }
	friend Complex operator - (const Complex & x, const Complex & y) { return Complex(x.a - y.a, x.b - y.b); }
};

Complex a[N], b[N], c[N];
db q[N], E[N];

void FFT(Complex P[], int n, int oper)
{
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
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
int main() {
	setIO("test");
	
	n=gi;
	int m=1;
	while (m < n << 1) m <<= 1;
	rep(i,n) scanf("%lf", &q[i]), E[i]=0;
	rep(i,n) a[i].a = (db)1 / i / i, b[i].a = q[i];
	a[0].a = 0;
	
	FFT(a, m, 1);
	FFT(b, m, 1);
	rep(i,m) c[i] = a[i] * b[i];
	FFT(c, m, -1);
	rep(i,n) c[i].a /= m;
	
	rep(i,n) E[i]=c[i].a;
	
	rep(i,m) b[i].a = b[i].b = 0.;
	rep(i,n) b[i].a = q[n-1-i];
	FFT(b, m, 1);
	rep(i,m) c[i] = a[i] * b[i];
	FFT(c, m, -1);
	rep(i,n) c[i].a /= m;
	
	rep(i,n) E[n-1-i]-=c[i].a;
	
	rep(i,n) printf("%.6f\n", E[i]);
	
	return 0;   
}
