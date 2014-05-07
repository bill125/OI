// Author: bill125
// ntr czr
// orz zyx
// using namespace inline

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
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1, maxn=200000+10, maxm=maxn*2;
int n, cnt;
ll ans;
struct Edge {
	int y;ll v;
	Edge *next;
	Edge (int _y,ll _v,Edge *_next) : y(_y), v(_v), next(_next) {}
}*h[maxm];
int q[maxn], fk[maxn][3], p[maxn];
ll f[maxn][3], g[maxn], t[maxn][2], tk[maxn][2], len[maxn];
bool v[maxn];
void Add_Edge(int x,int y,int c) {
	h[x]=new Edge(y,c,h[x]);
	h[y]=new Edge(x,c,h[y]);
}

void DFS(int x,ll Maxt,ll Len) {
	ForE(e,x) {
		ll t1,t2,t3;
		int y=e->y;
		if (y!=p[x]) {
			if (y==tk[x][0]) t1=t[x][1];
			else t1=t[x][0];
			maxe(t1,Maxt);
			if (y==fk[x][0]) {
				t2=f[x][1];
				t3=f[x][1]+f[x][2];
			}
			else {
				t2=f[x][0];
				if (y==fk[x][1]) t3=f[x][0]+f[x][2];
				else t3=f[x][0]+f[x][1];
			}
			maxe(t3,Len+t2);
			maxe(t3,Maxt);
			if (y==tk[x][0]) maxe(t3,t[x][1]);
			else maxe(t3,t[x][0]);
			
			if (max(g[y], t3)<ans) ++ cnt;
			
			DFS(y, t3 , max(Len, t2)+len[y]);
		}
	}
}

int main() {
	setIO("test");
	
	n=gi;
	fill(h,0);
	rep(i,n-1) {
		int a=gi-1, b=gi-1, c=gi;
		Add_Edge(a,b,c);
	}
	int r=1; q[0]=0, p[0]=-1;
	fill(v,0), v[0]=1;
	rep(i,n) {
		int x=q[i];
		ForE(e,x) {
			int y=e->y;
			if (!v[y]) {
				q[r++]=y, p[y]=x, len[y]=e->v;
				v[y]=1;
			}
		}
	}

	fill(f,0), fill(fk,-1);
	ans=cnt=0;
	repD(i,n) {
		int x=q[i];
		ForE(e,x) {
			int y=e->y;
			if (p[x]!=y) {
				rep(j,3) if (f[y][0]+e->v>f[x][j]) {
					ForD(k,2,j+1) f[x][k]=f[x][k-1], fk[x][k]=fk[x][k-1];
					f[x][j]=f[y][0]+e->v, fk[x][j]=y;
					break;
				}
				rep(j,2) if (g[y]>t[x][j]) {
					ForD(k,1,j+1) t[x][k]=t[x][k-1], tk[x][k]=tk[x][k-1];
					t[x][j]=g[y], tk[x][j]=y;
					break;
				}
				maxe(g[x],g[y]);
			}
		}
		maxe(g[x],f[x][0]+f[x][1]);
		maxe(ans,g[x]);
	}
	
	DFS(0,0,0);
	
	printf("%lld\n%d\n", ans, cnt);
	
	return 0;
}
