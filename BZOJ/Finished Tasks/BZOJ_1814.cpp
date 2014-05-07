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

const int inf=~0U>>1, maxn=15;
int n,m;
int a[maxn];
char c[maxn][maxn];
bool ok[maxn][maxn];
struct Status {
	int hash;
	Status () { hash=0; }
	bool operator<(const Status &b) const { return hash<b.hash; }

};
int ReCode(int a[]) {
	int hash=0;
	rep(i,m+1) hash=hash*3+a[i];
	return hash;
}
map<Status,ll> f[maxn][maxn];

void upd(int i,int j,Status & s, ll now) {
	if (f[i][j].count(s)) f[i][j][s]+=now;
	else {
	//	rep(k,m+1) printf("%d", s.a[k]);printf(" %d\n", s.hash);
		f[i][j][s]=now;
	}
}

int find(int a[], int lab, int step, int c) {
	int cnt=1;
	for (int i=lab; ;i+=step) {
		if (a[i]==c) --cnt;
		if (a[i]==3-c) ++cnt;
		if (!cnt) return i;
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) scanf("\n%s", c[i]);	
	bool flag=0;
	repD(i,n) {
		repD(j,m) if (c[i][j]=='.') {ok[i][j]=flag=1; break;}
		if (flag) break;
	}
	Status t;f[0][0][t]=1;
	
	rep(i,n) rep(j,m) {
		int ti=(j==m-1)?(i+1):i, tj=(j==m-1)?0:(j+1);
		ForV(now,f[i][j]) {
			Status x=now->first;
			int hash=x.hash;
			repD(k,m+1) a[k]= hash%3, hash/=3;
			if (j==0) { repD(k,m) a[k+1]=a[k]; a[0]=0; }
			ll t=now->second;
			if (c[i][j]=='*') {
				if (a[j]==0 && a[j+1]==0) {
					x.hash=ReCode(a);
					upd(ti,tj,x,t);
				}
				continue;
			}
			if (a[j]) {
				if (a[j+1]) {
					if (a[j]==1) {
						if (a[j+1]==1) {
							int k=find(a, j+2, 1, 2);
							a[k]=1;
						}
						else {
							if (!ok[i][j]) continue;
						}
					}
					else {
						if (a[j+1]==1) {
						}
						else {
							int k=find(a, j-1, -1, 1);
							a[k]=2;
						}
					}
					a[j]=a[j+1]=0, x.hash=ReCode(a);
					upd(ti, tj, x, t);
				}
				else {
					x.hash=ReCode(a);
					if (i!=n-1) upd(ti, tj, x, t);
					swap(a[j], a[j+1]), x.hash=ReCode(a);
					if (j!=m-1) upd(ti, tj, x, t);
				}
			}
			else {
				if (a[j+1]) {
					x.hash=ReCode(a);
					if (j!=m-1) upd(ti, tj, x, t);
					swap(a[j], a[j+1]), x.hash=ReCode(a);
					if (i!=n-1) upd(ti, tj, x, t);
				}
				else {
					a[j]=1, a[j+1]=2;
					x.hash=ReCode(a);
					if (i!=n-1 && j!=m-1) upd(ti, tj, x, t);
				}
			}
		}
	}
	
	ll ans;
	if (!f[n][0].count(t)) ans=0;
	else ans=f[n][0][t];
	printf("%lld\n", ans);
	
	return 0;
}
