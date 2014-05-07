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

const int inf=~0U>>1, maxn=300+10, maxm=1000000+10;
int n, m;
int f[maxn][maxn], id[maxn][maxn];
bool v[maxn];
db c[maxn][maxn], ans[maxm];
queue<int> q;

void bfs(int a,int b,db p) {
	fill(v, 0);
	for (q.push(a); !q.empty(); q.pop()) {
		int x=q.front();
		rep(y,n) if (id[x][y]>=0 && f[a][x]+f[b][y]+1==f[a][b]) {
			ans[id[x][y]]+=p / c[a][b] * (c[a][x] * c[b][y]);
			if (v[y]) continue;
			q.push(y);v[y]=1;
		}
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) rep(j,n) f[i][j]=10000000;
	fill(id, -1);
	rep(i,m) {
		int a=gi-1, b=gi-1;
		f[a][b]=f[b][a]=1;
		id[a][b]=id[b][a]=i;
	}
	
	rep(k,n) rep(i,n) rep(j,n) f[i][j]=min(f[i][j], f[i][k] + f[k][j]);
	rep(i,n) {
		rep(j,n) c[i][j]=0;
		c[i][i]=1, f[i][i]=0;
		for (fill(v, 0), q.push(i), v[i]=1; !q.empty(); q.pop()) {
			int x=q.front();
			rep(y,n) if (id[x][y] >= 0) {
				if (f[i][x] + 1 == f[i][y]) c[i][y] += c[i][x];
				if (v[y]) continue;
				v[y]=1;q.push(y);
			}
		}
	}
	
	rep(i,n) rep(j,n) {
		int p=gi; if (p) bfs(i, j, p);
	}
	
	rep(i,m) printf("%.1f\n", ans[i]);
	
	return 0;   
}
