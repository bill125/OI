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
#define abs(a) ((a)>0?(a):-(a))
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

const int inf=~0U>>1, maxn=500+10, maxm=250000+10;
int n,m;
int x[maxm], y[maxm], r[maxn];
db f[maxn], cnt[maxm];
inline bool equal(db a, db b) {
	return abs(a-b) < 0.000001;
}
struct Gauss {
	int n;
	db a[maxn][maxn];
	void work() {
		rep(i,n) {
			For(j,i,n-1) if (!equal(a[j][i],0)) {
				rep(k,n+1) swap(a[i][k],a[j][k]);
				break;
			}
			For(j,i+1,n-1) {
				db t=a[j][i]/a[i][i];
				For(k,i,n) a[j][k]-=a[i][k]*t;
			}
		}
		repD(i,n) {
			For(j,i+1,n-1) a[i][n]-=a[i][j]*a[j][n];
			a[i][n]/=a[i][i], a[i][i]=1;
		}
	}
}T;

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) ++r[x[i]=gi-1], ++r[y[i]=gi-1];
	
	T.n=n-1;
	T.a[0][n-1]=-1;
	rep(i,n-1) T.a[i][i]=-1;
	rep(i,m) {
		if (x[i]==n-1 || y[i]==n-1) continue;
		T.a[x[i]][y[i]]=(db)1/r[y[i]];
		T.a[y[i]][x[i]]=(db)1/r[x[i]];
	}
	
	T.work();
	
	rep(i,n-1) f[i]=T.a[i][n-1];f[n-1]=0;
	rep(i,m) cnt[i]=f[x[i]]/r[x[i]] + f[y[i]]/r[y[i]];
	sort(cnt,cnt+m);
	
	db ans=0;
	rep(i,m) {
		db len=m-i;
		ans+=len*cnt[i];
	}
	printf("%.3f\n", ans);
	
	return 0;
}
