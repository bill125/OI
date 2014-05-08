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
	string in=NAME+".in", out=NAME+"2.out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=5000+10, maxe=400000+10;
int n,m;
bool f[maxn][maxn];
bool v[maxn];

struct Edge {
	int y;
	Edge *next;
}*h[maxn], mem[maxe], *e=mem;

Edge *makeedge(int x,int y) {
	e->y=y;e->next=h[x];
	return e++;
}

void Add_Edge(int x,int y) {
	h[x]=makeedge(x, y);
}

queue<int> q;
void bfs(int s) {
	for (q.push(s); !q.empty(); q.pop()) {
		int x=q.front();
		rep(y,n) if (f[x][y]) {
			if (!v[y]) {
				v[y]=1; q.push(y);
			}
		}
	}
}

int main() {
	setIO("compound");
	
	int ans=0;
	n=gi, m=gi;
	rep(i,m) {
		int a=gi-1, b=gi-1;
		f[a][b]=f[b][a]=1;
	}
	
	int q=gi;
	rep(i,q) {
		scanf("\n");
		char style=getchar();
		if (style=='Q') {
			int ans=0;
			fill(v, 0);
			rep(i,n) if (!v[i]) {
				bfs(i);++ans;
			}
			printf("%d\n", ans);
		}
		else if (style=='A') {
			int x=gi-1, y=gi-1;
			f[x][y]=f[y][x]=1;
		}
		else {
			int x=gi-1, y=gi-1;
			f[x][y]=f[y][x]=0;
			
		}
	}
	
	return 0;   
}
