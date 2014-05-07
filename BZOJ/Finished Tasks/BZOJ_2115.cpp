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
	#ifndef ONLINE_JUDGE
	string in = NAME + ".in";
	string out = NAME + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
	#endif
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

const int inf=~0U>>1, maxn=50000+10, maxm=100000+10;
int n,m,r=0;
ll a[maxm*2], d[maxm*2];
bool v[maxn];
struct Edge {
	int y;
	ll v;
	Edge *next;
	Edge (int _y,ll _v,Edge *_next) : y(_y), v(_v), next(_next) {}
}*h[maxn];

void Add_Edge(int x,int y,ll z) {
	h[x]=new Edge(y,z,h[x]);
	h[y]=new Edge(x,z,h[y]);
}

int gauss()
{
	int k=1;
	repD(i,64) {
		int t=0;
		For(j,k,r) if ((a[j]>>i-1)&1) t=j;
		if (!t) continue;
		swap(a[k],a[t]);
		For(j,k+1,r) if ((a[j]>>i-1)&1) a[j]^=a[k];
		++k;
	}
	return --k;
}

void DFS(int x) {
	v[x]=1;
	ForE(i,x) {
		int y=i->y;
		if (!v[y]) {
			d[y]=d[x]^i->v;
			DFS(y);
		}
		else a[++r]=d[x]^d[y]^i->v;
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) {
		int x=gi, y=gi;
		ll z=gi;
		Add_Edge(x,y,z);
	}
	fill(v,0);
	DFS(1);
	ll ans=d[n];
	int tot=gauss();
	For(i,1,tot) ans=max(ans,ans^a[i]);
	printf("%lld\n", ans);
	
	return 0;
}
