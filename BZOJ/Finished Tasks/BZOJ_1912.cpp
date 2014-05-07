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

const int inf=~0U>>1, maxn=100000+10, maxm=maxn<<1;
int n, m;
int dp[maxn][4], from[maxn][4], p[maxn], q[maxn];
int g[maxn], f[maxn][4], from2[maxn][4];
bool v[maxn];
struct Edge {
	int y;
	Edge *next;
}mem[maxm], *h[maxn], *E=mem;

void Add_Edge(int a,int b) {
	E->next=h[a], E->y=b, h[a]=E;
	E++;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n-1) {
		int a=gi-1, b=gi-1;
		Add_Edge(a, b), Add_Edge(b, a);
	}
	int r=1; q[0]=0, p[0]=-1;v[0]=1;
	rep(i,r) {
		int x=q[i];
		ForE(e,x) {
			int y=e->y;
			if (!v[y]) { 
				v[y]=1; q[r++]=y;
				p[y]=x;
			}
		}
	}
	
	fill(from, -1);
	repD(i,n) {
		int x=q[i];
		ForE(e,x) { int y=e->y; 
			if (y==p[x]) continue;
			rep(j,4) if (from[x][j] == -1 || dp[y][0] + 1 > dp[x][j]) {
				ForD(k,3,j+1) dp[x][k] = dp[x][k-1], from[x][k] = from[x][k-1];
				dp[x][j] = dp[y][0] + 1, from[x][j] = y;
				break;
			}
		}
	}
	
	if (m==1) {
		int ans=0;
		rep(i,n) ans = max(ans, dp[i][0] + dp[i][1]);
		ans = (n-1) * 2 - ans + 1;
		printf("%d\n", ans);
	}
	else {
		int ans=0;
		fill(from2, -1);
		rep(i,n) {
			int x=q[i];
			ForE(e,x) { int y=e->y;
				if (p[x] == y) continue;
				int t=from[x][0]==y;
				rep(j,4) if (from[y][j] == -1 || dp[x][t] + 1 > dp[y][j]) {
					ForD(k,3,j+1) dp[y][k] = dp[y][k-1], from[y][k] = from[y][k-1]; 
					dp[y][j] = dp[x][t] + 1, from[y][j] = x;
					break;
				}
			}
		}
		repD(i,n) {
			int x=q[i];
			ans = max(ans, dp[x][0] + dp[x][1] + dp[x][2] + dp[x][3]);
			ForE(e,x) {
				int y=e->y;
				if (p[x] == y) continue;
				rep(j,4) if (from2[x][j]==-1 || f[y][0] > f[x][j]) {
					ForD(k,3,j+1) f[x][k] = f[x][k-1], from2[x][k] = from2[x][k-1];
					f[x][j] = f[y][0], from2[x][j] = y;
					break;
				}
			}
			
			rep(j,4) if (from2[x][j] == -1) { from2[x][j] = x; break; }
			rep(j,4) For(k,j+1,3) {
				int t=0;
				while (from2[x][t] != -1  && (from2[x][t] == from[x][j] || from2[x][t] == from[x][k])) ++t;
				ans = max(ans, dp[x][j] + dp[x][k] + f[x][t]);
			}
			ans = max(ans, f[x][0] + f[x][1]); 
		
			int t;
			if (from[x][0] == p[x]) t=dp[x][1] + dp[x][2];
			else if (from[x][1] == p[x]) t=dp[x][0] + dp[x][2];
			else t = dp[x][0] + dp[x][1];
			if (t>f[x][0]) f[x][0]=t;
		}
		
		ans = (n-1) * 2 - ans + 2;
		printf("%d\n", ans);
	}
	
	return 0;   
}
