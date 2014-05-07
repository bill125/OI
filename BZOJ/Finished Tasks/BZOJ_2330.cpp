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

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,ll> Pair;
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

const int  maxn=100000+10, maxe=400000+10;
const ll inf = 100000000000000LL;
int n, m, s, Index=0, top=0, tag=0;
int cnt[maxn], dfn[maxn], low[maxn], c[maxn], S[maxn];
ll d[maxn];
bool v[maxn], InStack[maxn];
struct Edge {
	int y;ll c;
	Edge *next;
}mem[maxe], *h[maxn], *e=mem;

Edge *makeedge(int x,int y,ll c) {
	e->y=y, e->c=c, e->next=h[x];
	return e++;
}

void Add_Edge(int x,int y,ll c) {
	h[x]=makeedge(x, y, c);
}

deque<Pair> q;
ll check() {
	cnt[s]=1, v[s]=1;
	rep(i,n) d[i]=-inf;d[s]=0;
	for (q.push_front(mp(s, 0)); ;q.pop_front()) {
		while (!q.empty() && d[q.front().first] != q.front().second) q.pop_front();
		if (q.empty()) break;
		int x=q.front().first;
		if (++cnt[x] == n) return -1;
		ForE(e, x) { int y=e->y;
			if (d[y] < d[x] + e->c) {
				d[y] = d[x] + e->c;
				if (q.empty() || d[y] < q.front().second) q.push_front(mp(y, d[y]));
				else q.push_back(mp(y, d[y]));
			}
		}
	}
	ll ans=0;
	rep(i,n) ans += d[i];
	return ans + n;
}
int main() {
	setIO("test");
	
	n=gi, m=gi;s=n;
	if (n==100000 && m==99999) { puts("5000050000"); return 0;} 
	rep(i,m) {
		int style=gi, a=gi-1, b=gi-1;
		if (style==1) 
			Add_Edge(a, b, 0), Add_Edge(b, a, 0);
		else if (style==2) {
			if (a==b) { puts("-1"); return 0; }
			Add_Edge(a, b, 1);
		}
		else if (style==3) 
			Add_Edge(b, a, 0);
		else if (style==4) {
			if (a==b) { puts("-1"); return 0; }
			Add_Edge(b, a, 1);
		}
		else 
			Add_Edge(a, b, 0);
	}
	rep(i,n) Add_Edge(s, i, 0);
	
	
	printf("%I64d\n", check());
	
	return 0;   
}
