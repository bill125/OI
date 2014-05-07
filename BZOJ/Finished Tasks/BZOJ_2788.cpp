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

const int inf = ~0U>>1,maxn = 600+10,maxe = 200000+10;
int n,m1,m2,tot = -1,cColor = 0;
int c[maxn],h[maxn],f[maxn][maxn],Max[maxn];
struct Edge {
	int to,next,len;
}E[maxe];

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

void addedge(int a,int b,int c) {
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot,E[tot].len = c;
}

namespace SCC {
	const int maxn = 600+10;
	int dfn[maxn],low[maxn],Stack[maxn],Top = 0,Index = 0;
	bool InStack[maxn];
	
	void init() {
		rep(i,n) dfn[i] = 0;
		fill(InStack,0);
	}
	
	void Tarjan(int x,int *c) {
		Stack[Top++] = x;
		InStack[x] = true;
		dfn[x] = low[x] = ++Index;
		ForE(i,x) {
			int y = E[i].to;
			if (!dfn[y]) {
				Tarjan(y,c);
				low[x] = min(low[x],low[y]);
			}
			else if (InStack[y]) low[x] = min(low[x],dfn[y]);
		}
		if (dfn[x] == low[x]) {
			int now;
			do {
				now = Stack[--Top];
				c[now] = cColor;
				InStack[now] = 0;
			} while (Top && now != x);
			++cColor;
		}
	}
}

void Fail() {puts("NIE");}

int main() {
	setIO("test"); 
	n = gi,m1 = gi,m2 = gi;
	rep(i,n) h[i] = c[i] = -1;
	int a,b;
	rep(i,m1) {
		a = gi-1,b = gi-1;
		addedge(a,b,1),addedge(b,a,-1);
	}
	rep(i,m2) {
		a = gi-1,b = gi-1;
		addedge(a,b,0);
	}
	
	SCC::init();
	
	rep(i,n) if (c[i] == -1) SCC::Tarjan(i,c);
	rep(i,n) rep(j,n) f[i][j] = -inf;
	rep(i,n) f[i][i] = 0;
	rep(i,n) ForE(k,i) {
		int j = E[k].to;
		if (c[i] == c[j]) f[i][j] = max(f[i][j],E[k].len);
	}

	//debug(c,n);
	rep(k,n) rep(i,n) rep(j,n) if (f[i][k] != -inf && f[k][j] != -inf) {
		f[i][j] = max(f[i][j],f[i][k] + f[k][j]);
	//	printf("%d->%d->%d %d+%d\n", i+1,k+1,j+1,f[i][k],f[k][j]);
	}
	rep(i,n) if (f[i][i]>0) {Fail();return 0;}
	rep(i,n) rep(j,n) if (c[i] == c[j]) Max[c[i]] = max(Max[c[i]],abs(f[i][j]));
	int ans = 0;
	rep(i,cColor) ans += Max[i]+1;
	printf("%d\n", ans);
	
	return 0;
}
