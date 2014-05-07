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
#define ForS(i,a,b,step) for (int i = a;i != b;i += step)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define ForV(i,a) for (__typeof (a.begin()) i = a.begin();i != a.end();++i) 
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()

const int inf = ~0U>>1,maxn = 100000+10,maxe = 400000+10;
int n,m,tot = -1;
int h[maxn],d[maxn],q[maxn];
struct Edge {
	int to,next;
	bool v;
}E[maxe];
bool v[maxn];

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

void addedge(int x,int y) {
	++tot;
	E[tot].to = y,E[tot].next = h[x],h[x] = tot;
	E[tot].v = false;
}

int main() {
	setIO("test"); 
	
	scanf("%d %d", &n, &m);
	rep(i,n) h[i] = -1;
	rep(i,m) {
		int a = gi-1,b = gi-1;
		++d[a],++d[b];
		addedge(a,b),addedge(b,a);
	}
	
	fill(v,0);
	int r = 0;
	rep(i,n) if (d[i] == 1) q[++r] = i; 
	
	bool ans = true;
	For(i,1,r) {
		if (!d[q[i]]) {ans = false;break;}
		ForE(j,q[i]) if (!E[j].v) {
			E[j].v = E[j^1].v = 1;
			--d[q[i]],--d[E[j].to];
			v[q[i]] = 1;
			if (1==d[E[j].to]) q[++r] = E[j].to;
		}
	}
	
	rep(i,n) if (!v[i] && !d[i]) {ans = false;break;}
	
	if (ans) printf("TAK\n");
	else printf("NIE\n");
		
	return 0;
}
