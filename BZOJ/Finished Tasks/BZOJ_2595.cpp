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

const int inf=~0U>>1,maxn=11,maxm=10,maxM=(1<<10)+10;
int n,m;
int a[maxn][maxn], ans[maxn][maxn];
struct status {
	bool choose;
	int a[maxm];
	status () {fill(a,0);}
	inline bool operator<(const status&B) const{
		rep(i,m) {
			if (a[i]<B.a[i]) return 1;
			if (a[i]>B.a[i]) return 0;
		}
		return 0;
	}
	void rearrange() {
		int t[12], tag=1;
		fill(t,-1);
		t[0]=0;
		rep(i,m) 
			if (t[a[i]]==-1)
				t[a[i]]=tag++;
		rep(i,m) a[i]=t[a[i]];				
	}
	bool only(int j) {
		if (a[j]==0) return 0;
		rep(i,m) 
			if (j!=i && a[i]==a[j])
				return 0;
		return 1;
	}
	void change(int x,int y) {
		rep(i,m)
			if (a[i]==x)
				a[i]=y;
	}
};
map<status,int> dp[maxn][maxm];
map<status,const status*> prev[maxn][maxm];


int main() {
	setIO("test");
	
	n=gi, m=gi;
	For(i,1,n) rep(j,m) a[i][j]=gi;
	
	status tmp;tmp.choose=0;
	dp[0][m-1][tmp]=0;
	
	rep(i,n+1) rep(j,m) {
		if (i==n && j==m-1) break;
		if (j==m-1) {
			ForV(k,dp[i][j]) {
				status now=k->v1;
				//choose
				now.choose=1;
				if (now.a[0]==0) {
					now.a[0]=m+1;
					now.rearrange();
				}
				if (!dp[i+1][0].count(now) || k->v2+a[i+1][0]<dp[i+1][0][now]) {
					dp[i+1][0][now]=k->v2+a[i+1][0];
					prev[i+1][0][now]=&k->v1;
				}
				//dump
				now=k->v1;
				if (!now.only(0) && a[i+1][0]) {
					now.choose=0;
					now.a[0]=0;
					if (!dp[i+1][0].count(now) || k->v2<dp[i+1][0][now]) {
						dp[i+1][0][now]=k->v2;
						prev[i+1][0][now]=&k->v1;
					}
				}
			}
			continue;
		}

		ForV(k,dp[i][j]) {
			status now=k->v1;
			//choose
			now.choose=1;
			if (now.a[j]||now.a[j+1]) {
				if (now.a[j]&&now.a[j+1]) {
					now.change(now.a[j],now.a[j+1]);
					now.rearrange();
				}
				else if (now.a[j]) now.a[j+1]=now.a[j];
			}
			else {
				now.a[j+1]=m+1;
				now.rearrange();
			}
			if (!dp[i][j+1].count(now) || k->v2+a[i][j+1]<dp[i][j+1][now]) {
				dp[i][j+1][now]=k->v2+a[i][j+1];
				prev[i][j+1][now]=&k->v1;
			}
			
			//dump
			now=k->v1;
			if (!now.only(j+1) && a[i][j+1]) {
				now.choose=0;
				now.a[j+1]=0;
				if (!dp[i][j+1].count(now) || k->v2<dp[i][j+1][now]) {
					dp[i][j+1][now]=k->v2;
					prev[i][j+1][now]=&k->v1;
				}
			}
			
		}
	}
	status now;
	int tans=inf;
	ForV(i,dp[n][m-1]) {
		bool flag=1;
		rep(j,m) if (i->v1.a[j]>1) {
			flag=0; break;
		}
		if (!flag) continue;
		if (i->v2<tans) {
			tans=i->v2;
			now=i->v1;
		}
	}
	
	ForD(i,n,1) repD(j,m) {
		if (a[i][j]==0) ans[i][j]=2;
		else ans[i][j]=now.choose;
		now=*prev[i][j][now];
	}
	
	char c[3];
	c[0]='_', c[1]='o', c[2]='x';
	printf("%d\n", tans);
	For(i,1,n) {
		rep(j,m) printf("%c", c[ans[i][j]]);
		puts("");
	}
	
	return 0;
}
