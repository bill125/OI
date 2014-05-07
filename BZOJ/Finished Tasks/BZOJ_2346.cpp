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

const int inf=~0U>>1, maxn=500+10, maxp=300000+10, maxe=maxp*4;
int n,m,e=0;
char a[maxn][maxn];
int dis[maxp];
int x[maxe], y[maxe], z[maxe], num[maxe];
deque<Pair> q;

struct Edge {
	int y, c;
	Edge *next;
	Edge (int _y, int _c, Edge *_next) : y(_y), c(_c), next(_next) {} 
}*h[maxp];

int code(int x,int y) {
	return x*(m+1) + y;
}

void Add_Edge(int a,int b,int c) {
	x[e]=a, y[e]=b, z[e]=c, num[e]=e;
	++e;
}

void Build(int x,int y,int c) {
	h[x]=new Edge(y, c, h[x]);
}

bool cmp(int a,int b) {
	return z[a] > z[b];
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	if ((n+m) & 1) {
		puts("NO SOLUTION");
		return 0;
	}
	rep(i,n) scanf("%s", a[i]);
	
	int s=code(0, 0);
	int t=code(n, m);
	rep(i,n+1) for (int j=i&1; j<=m; j+=2) {
		if (i) {
			if (j)   Add_Edge(code(i,j), code(i-1,j-1), a[i-1][j-1]=='/');
			if (j<m) Add_Edge(code(i,j), code(i-1,j+1), a[i-1][j]  !='/');
		}
		if (i<n) {
			if (j)   Add_Edge(code(i,j), code(i+1,j-1), a[i][j-1]!='/');
			if (j<m) Add_Edge(code(i,j), code(i+1,j+1), a[i][j]  =='/');
		}
	}
	sort(num, num+e, cmp);
	rep(_i, e) {
		int i=num[_i];
		Build(x[i], y[i], z[i]);
	}
	
	fill(dis, 127); dis[s]=0; 
	for (q.clear(), q.pb(mp(s, dis[s])) ;; ) {
		for ( ; !q.empty() && dis[q.front().first]!=q.front().second; q.pop_front()) ; 
		if (q.empty()) break;
		int x=q.front().first;q.pop_front();
		ForE(e,x) {
			int y=e->y;
			if (dis[x] + e->c < dis[y]) {
				dis[y] = dis[x] + e->c;
				if (!e->c) q.push_front(mp(y, dis[y]));
				else q.push_back(mp(y, dis[y]));
			}
		}
	}
	printf("%d\n", dis[t]);
	
	return 0;   
}
