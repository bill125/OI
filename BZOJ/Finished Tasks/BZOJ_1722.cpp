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

const int inf=1000000000, maxn=500+10;
int n,m;
int a[maxn], q[maxn], cnt[maxn];
int f[maxn][maxn][2], g[maxn];
struct Edge {
	int y;
	Edge *next;
	Edge (int _y, Edge *_next) : y(_y), next(_next) {}
}*h[maxn];

inline void upd(int & a,int b) { if(b>a)a=b; }

void Add_Edge(int x,int y) {
	h[x]=new Edge (y, h[x]); 
}

void work(int x) {
	cnt[x]=1;
	rep(i,2) f[x][0][i]=a[x]*i;
	ForE(e,x) {
		int y=e->y;
		work(y);
		cnt[x]+=cnt[y];
		rep(p,2) {
			For(i, 0, cnt[x]-1) g[i]=f[x][i][p];
			For(j, 0, cnt[y]-1) 
				rep(q,2) For(i, (p&q)+j, cnt[x]-1) upd( f[x][i][p], g[i-j-(p&q)]+f[y][j][q] );
		}
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) rep(j,n) rep(k,2) f[i][j][k]=-inf;
	For(i,1,n) {
		a[i]=gi;int x=gi;
		Add_Edge(x, i);
	}
	
	work(0);
	
	int ans=-1;
	repD(i,n) if (f[0][i][0]>=m) {
		ans=i; break;
	}
	printf("%d\n", ans);
	
	return 0;
}
