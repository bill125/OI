#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define ForV(i,a) for (__typeof (a.begin()) i = a.begin();i != a.end();++i) 
#define fill(a,b) memset(a,b,sizeof(a))
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define gi gI()

const int inf = ~0U>>1,maxv = 1000000+10,maxn = 100000+10;
int n,l,r;
int a[maxn],X[maxv],Y[maxv][2],Yj[maxv][2],q[maxv],ss[maxv]; 
bool V[maxv];
vector<int> Q[maxn];

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

int gI() {
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

void debug(int *a,int n) {rep(i,n) printf("%d ", a[i]);puts("");}

void getss() {
	l = 0;
	For(i,2,1000) {
		bool flag = 1;
		rep(j,l) if (!(i%ss[j])) {
			flag = 0;break;
		}
		if (flag) ss[l++] = i;
	}
}

int getX(int x) {
	int res = 0;
	rep(i,l) {
		if (x == 1) break;
		while (x % ss[i] == 0) x /= ss[i],++res;
	}
	if (x != 1) ++ res;
	return res;
}

int Ask(int x) {
	if (!X[x]) X[x] = getX(x);
	return X[x];
}

void getQ(int x,int *q,int & r) {
	r = 1,q[0] = 1;
	rep(i,l+1) {
		if (i == l && x != 1) ss[i] = x;
		int _r = r,t = 1;
		while (x % ss[i] == 0) {
			x /= ss[i],t *= ss[i];
			rep(j,_r) V[q[r++] = q[j] * t] = 1;
		}
		if (x == 1) break;
	}
}

int main() {
	setIO("test"); 
	
	getss();
	n = gi;
	rep(i,n) a[i] = gi,X[a[i]] = getX(a[i]);
	fill(V,0);
	rep(i,n) {
		getQ(a[i],q,r);
		rep(j,r) Q[i].pb(q[j]);
	}

	fill(Y,127);
	rep(i,n) {
		int t = X[a[i]];
		rep(k,Q[i].size()) {
			int j = Q[i][k];
			if (t < Y[j][0] || t == Y[j][0] && i < Yj[j][0]) {
				Y[j][1] = Y[j][0];
				Yj[j][1] = Yj[j][0];
				Y[j][0] = t;
				Yj[j][0] = i;
			} 
			else 
				if (t < Y[j][1] || t == Y[j][1] && i < Yj[j][1]) {
					Y[j][1] = t;
					Yj[j][1] = i;
				}
		}
	}
	
	For(i,1,maxv-10) if (V[i]) rep(j,2) Y[i][j] -= Ask(i)*2;
	
	rep(i,n) {
		int t = X[a[i]],ans = inf,ansj;
		rep(k,Q[i].size()) {
			int j = Q[i][k];
			if (Yj[j][0] == i) {
				if (Y[j][1] + t < ans || Y[j][1] + t == ans && Yj[j][1] < ansj) {
					ans = Y[j][1] + t;
					ansj = Yj[j][1];
				}
			}
			else 
				if (Y[j][0] + t < ans || Y[j][0] + t == ans && Yj[j][0] < ansj) {
					ans =  Y[j][0] + t;
					ansj = Yj[j][0];
				}
		}
		printf("%d\n", ansj+1);
	}
	
	return 0;
}
