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

const int inf=~0U>>1, maxn=500000+10;
int n;
int p[maxn], q[maxn];
db dp[maxn][2], c[maxn], f[maxn], len[maxn];

struct Edge {
	int y; db c;
	Edge *next;
	Edge(int _y, db _c, Edge *_next) : y(_y), c(_c), next(_next) {}
}*h[maxn];

void Add_Edge(int a,int b, db c){
	h[a]=new Edge(b, c, h[a]);
}

int main() {
	setIO("charger");
	
	n=gi;
	rep(i,n-1) {
		int a=gi-1, b=gi-1;db c=gi;
		c/=100;
		Add_Edge(a, b, c);
		Add_Edge(b, a, c);
	}
	int r=1;
	q[0]=0;p[0]=-1;
	rep(i,r) {
		int x=q[i];
		ForE(e,x) { int y=e->y;
			if (y!=p[x]) {
				p[y]=x;
				len[y]=e->c;
				q[r++]=y;
			}
		}
	}
	rep(i,n) c[i]=gi, c[i]/=100;
	
	repD(i,n) {
		int x=q[i];
		dp[x][0]=1-c[x];
		
		ForE(e,x) if (e->y != p[x]) {
			dp[x][0] *= (dp[e->y][0] + (1-dp[e->y][0]) * (1-e->c));
		}
	}
	
	f[0]=dp[0][0];
	dp[0][1]=1;
	
	db ans=1-f[0];
	For(i,1,n-1) {
		int x=q[i];
		db t;
		if (dp[x][0]+(1-dp[x][0])*(1-len[x])==0) t=0;
		else {
			t=dp[p[x]][0]/(dp[x][0]+(1-dp[x][0])*(1-len[x]));
			t*=dp[p[x]][1];
		}
		dp[x][1] = t + (1-t) * (1-len[x]);
		f[x] = dp[x][0] * dp[x][1];
		ans += 1-f[x];
	}

	printf("%.6f\n", ans);
	
	return 0;   
}
