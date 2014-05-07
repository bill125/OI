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
#define ForE(i,a) for (vector<Edge>::iterator i = E[a].begin();i != E[a].end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define pf push_front
#define gi gI()

const int inf = ~0U>>1,maxp = 600+10;
int n,m;
int w[maxp][maxp];

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

ll gI() {
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	ll p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

template <class T> void debug(const T &a,const int &n) {rep(i,n) cout << a[i] << " ";puts("");}

namespace KM {
	const int maxn = maxp;
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

int main() {
	setIO("test"); 
	
	m = gi,n = gi;
	
	fill(w,0);
	rep(i,n) rep(j,m) {
		int a = gi;
		rep(k,n) {
			w[i][j*n+k] = -a*(k+1);
		//	printf("%d %d %d\n", i+1,j*n+k+1,w[i][j*n+k]);
		}
	}
	KM::init(n*m,w);
	db ans = (db) -KM::km()/n;
	printf("%.2f\n", ans);
	
	return 0;
}
