//Author: bill125

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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define pb push_back
#define mp make_pair
#define v1 first
#define v2 second
#define gi gI()
#define cut puts("===================")

void setIO(string NAME) {
	string in = NAME + ".in";
	string out = NAME + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
}
ll gI() {
	char c=getchar();
	while ((c<'0' || c>'9')&&c!='-') c=getchar();
	ll flag=1,p=0;
	if (c=='-') flag=-1,c=getchar();
	while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();
	return p*flag;
}
int gs(char *C) {
	char c=getchar();
	while (c==' ' || c=='\n') c=getchar();
	int l=0;
	while (c!=' ' && c!='\n') C[l++]=c,c=getchar();
	C[l]=0;
	return l;
}

template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i], (i==n-1) ? '\n' : ' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=1000000000,maxn=250+10;
int n,m;
int e[maxn][maxn], f[maxn][maxn], d[maxn];
bool v[maxn][maxn], vis[maxn];

int ask() {
	fill(d,127), fill(vis,0);
	int x=0;d[0]=0,vis[0]=1;
	rep(i,n-1) {
		rep(j,n) if (e[x][j]) mine(d[j],e[x][j]+d[x]);
		int mind=inf, minj;
		rep(j,n) if (!vis[j] && d[j]<mind) 
			mind=d[j], minj=j;
		x=minj, vis[x]=1;
	}
	return d[n-1];
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	fill(e,0);
	rep(i,n) rep(j,n) f[i][j]=inf;
	rep(i,n) f[i][i]=0;
	rep(i,m) {
		int a=gi-1, b=gi-1, c=gi;
		e[a][b]=e[b][a]=f[a][b]=f[b][a]=c;
	}
	
	rep(k,n) rep(i,n) rep(j,n) 
		if (f[i][k]+f[k][j]<f[i][j])
			f[i][j]=f[i][k]+f[k][j];
			
	rep(i,n) rep(j,n) 
		if (f[0][i]+e[i][j]==f[0][j]) 
			v[i][j]=1;
	
	int ans=f[0][n-1];
	rep(x,n) rep(y,n) if (v[x][y] && e[x][y]) {
		e[x][y]<<=1, e[y][x]<<=1;
		int t=ask();
		maxe(ans,t);
		e[x][y]>>=1, e[y][x]>>=1;
	}
	
	printf("%d\n", ans-f[0][n-1]);
	
	return 0;
}
