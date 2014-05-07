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

const int inf = ~0U>>1,maxn = 100000+10,maxans = 10+1;
int n,m;
ll q;
int son[maxn],dp[maxn][3],P[maxn][2];
ll f[maxn][3][maxans];
vector<int> s[maxn];
bool v[maxn];

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

struct Edge {
	int t;
	Edge () {}
	Edge (int _t) : t(_t) {}
};
vector<Edge> E[maxn];

void Add_Edge(int x,int y) {
	E[x].pb(Edge(y));
}

void gets(int x) {
	v[x] = 1;
	son[x] = 0;
	ForE(e,x) 
		if (!v[e->t]) {
			++son[x];
			s[x].pb(e->t);
			gets(e->t);
		}
}

void work1(int x) {
	dp[x][0] = dp[x][1] = dp[x][2] = n+1;
	P[x][0] = P[x][1] = -1;
	
	rep(j,son[x]) {
		const int &t = s[x][j];
		work1(t);
		if (P[x][0] == -1 || dp[t][2] > dp[P[x][0]][2]) {
			P[x][1] = P[x][0];
			P[x][0] = t;
		}
		else 
			if (P[x][1] == -1 || dp[t][2] > dp[P[x][1]][2]) 
				P[x][1] = t;
	}
	int now = 0;
	rep(j,son[x]) {
		const int &t = s[x][j];
		now = max(now,dp[t][2]+1);
	}
	dp[x][0] = now;
	now = 0;
	rep(j,son[x]) {
		const int &t = s[x][j];
		if (t == P[x][0]) 
			now = max(now,min(dp[t][2]+1,dp[t][0]));
		else 
			now = max(now,dp[t][2]+1);
	}
	dp[x][0] = min(dp[x][0],now);
	
	now = 0;
	rep(j,son[x]) {
		const int &t = s[x][j];
		if (t == P[x][0] || t == P[x][1]) 
			now = max(now,min(dp[t][2]+1,dp[t][0]));
		else 
			now = max(now,dp[t][2]+1);
	}
	dp[x][1] = now;
	dp[x][2] = min(dp[x][1],dp[x][0]);
}

void work2(int x) {
	rep(j,son[x]) work2(s[x][j]);
	For(k,0,dp[0][2]) {
		f[x][0][k] = 1;f[x][1][k] = f[x][2][k] = 0;
		rep(j,son[x]) {
			const int &t = s[x][j];
			ll a = 0,b = 0;
			a = (f[t][0][k] + f[t][1][k]) % q;
			if (k == 0) b = 0;
			else b = (f[t][0][k-1] + f[t][1][k-1] + f[t][2][k-1]) % q;	
			f[x][2][k] = ((a * f[x][1][k]) % q + (b * f[x][2][k]) % q) % q; 
			f[x][1][k] = ((a * f[x][0][k]) % q + (b * f[x][1][k]) % q) % q;
			f[x][0][k] = (b * f[x][0][k]) % q;
		}
	}
}

int main() {
	setIO("test"); 
	
	n = gi,m = gi,q = gi;
	if (m != n-1) {
		puts("-1");
		puts("-1");
		return 0;
	}
	rep(i,m) {
		int a = gi-1,b = gi-1;
		Add_Edge(a,b),Add_Edge(b,a);
	}
	fill(v,0);
	gets(0);
	work1(0);
	
	printf("%d\n", dp[0][2]);
	
	work2(0);
	
	ll ans = 0;
	rep(i,3) ans = (ans + f[0][i][dp[0][2]]) % q;
	printf("%lld\n", ans);
	
	return 0;
}
