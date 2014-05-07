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

const int inf = ~0U>>1,maxn = 1000 + 10,maxe = 2000 + 10;
int n,m,e,c,eT = -1;
int h[maxn],f[maxn][maxn],d[maxn][maxn],pos[2][maxn][maxn];
bool v[maxn];
db dp[maxn][maxn],p[maxn];
struct Edge {
	int next,to;
}E[maxe];
vector<Edge> q;

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

void debug(int *a,int n) {rep(i,n) printf("%d ", a[i]);puts("");}
void debug(ll *a,int n) {rep(i,n) cout << a[i] << " ";puts("");}

bool cmp(Edge a,Edge b) {
	return a.next < b.next;
}

void Dijkstra(int x) {
	rep(i,n) f[x][i] = 100000;
	fill(v,0);v[x] = 1;
	f[x][x] = 0;
	int now = x;
	//vector<Edge> q;
	q.clear();
	Edge t;
	rep(i,n-1) {
		v[now] = 1;
		ForE(k,now) {
			int j = E[k].to;
			if (f[x][now] + 1 < f[x][j]) {
				t.to = j,t.next = f[x][now] + 1;
				q.pb(t);
				push_heap(q.begin(),q.end(),cmp);
			}
		}
		do {
			pop_heap(q.begin(),q.end(),cmp);
			t = q.back();
			q.pop_back();
		} while (v[t.to]);
		f[x][now = t.to] = t.next;
		
		int tmp = inf;
		rep(i,n) if (!v[i]) tmp = min(tmp,f[x][i]);
		if (tmp != t.next) puts("XXXX"); 
	}
}

void SPFA(int x) {
	int q[maxn];
	fill(q,0);
	rep(i,n) d[x][i] = 100000;
	d[x][x] = 0;
	int l = -1,r = 0;
	fill(v,0);
	q[0] = x;v[x] = 1;
	while (l != r) {
		l = l%maxn+1;
		ForE(i,q[l]) if (1 + d[x][q[l]] < d[x][E[i].to]) {
			d[x][E[i].to] = 1 + d[x][q[l]];
			if (!v[E[i].to]) {
				v[E[i].to] = 1;
				q[r=r%maxn+1] = E[i].to;
			}
		}
		v[q[l]] = 0;
	}
}

void addedge(int x,int y) {
	++eT;
	E[eT].to = y,E[eT].next = h[x],h[x] = eT;
}

void pre_work() {
	rep(i,n) rep(j,n) 
		if (i != j && f[i][j] > 1) {
			pos[0][i][j] = n+1;
			ForE(k,i) {
				int t = E[k].to;
				if (f[i][t] + f[t][j] == f[i][j]) 
					pos[0][i][j] = min(pos[0][i][j],t);
			}
		}
	
	rep(i,n) rep(j,n)
		if (i != j && f[i][j] > 2) {
			pos[1][i][j] = pos[0][pos[0][i][j]][j];
		}
}

void work(int x,int y) ;

db run(int x,int y) {
	if (dp[x][y] < 0) work(x,y);
	return dp[x][y];
}

void work(int x,int y) {
	if (x == y) {
		dp[x][y] = 0;
		return ;
	}
	if (f[x][y] <= 2) {
		dp[x][y] = 1;
		return ;
	}
	int x1 = pos[1][x][y];
	dp[x][y] = run(x1,y)*p[y];	
	ForE(j,y) {
		int i = E[j].to;
		dp[x][y] += run(x1,i)*p[y]; 
	}
	dp[x][y] += 1;
}

int main() {
	setIO("test"); 
	
	n = gi,e = gi;c = gi-1,m = gi-1;
	
	rep(i,n) h[i] = -1,p[i] = 1;
	rep(i,e) {
		int a = gi-1,b = gi-1;
		addedge(a,b);
		addedge(b,a);
		++p[a],++p[b];
	}
	rep(i,n) p[i] = 1/p[i];
	
	//rep(i,n) Dijkstra(i);
	rep(i,n) SPFA(i);
	
	rep(i,n) rep(j,n) f[i][j] = d[i][j];
	
	pre_work();
	rep(i,n) rep(j,n) dp[i][j] = -1;
	
	printf("%.3f\n", run(c,m));
	
	return 0;
}
