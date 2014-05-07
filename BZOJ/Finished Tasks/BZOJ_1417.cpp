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

const int inf=~0U>>1, maxn=30+10, MOD=10000007, p=233;
int n,m;
int f[maxn], cnt[maxn];

struct Status {
	int a[maxn],l,c;
	Status () { fill(a,0), l=0; }
	void MakeUp() { sort(a,a+l); }
	void Code() { c=0; rep(i,l) c=(c*p+a[i])%MOD; }
	bool operator<(const Status &O) const { return c<O.c; }
};
map<Status,db> dp;

int find(int x) {
	if (f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void merge(int x,int y) { x=find(x), y=find(y); if (x!=y) f[x]=y; }

void work(Status now) {
	if (now.l==1) {
		dp[now]=0;
		return ;
	}
	int l=now.l;
	db y=n*(n-1)/2, _dp=0, same=0;
	rep(i,l) same+=now.a[i]*(now.a[i]-1)/2;
	rep(i,l-1) For(j,i+1,l-1) {
		db x=now.a[i]*now.a[j];
		Status t=now;
		t.a[i]+=t.a[j], t.a[j]=t.a[l-1], --t.l;
		t.MakeUp(), t.Code();
		if (!dp.count(t)) work(t);
		_dp+=dp[t]*x/y;
	}
	dp[now]=(1+_dp)/(y-same)*y;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) f[i]=i;
	rep(i,m) {
		int x=gi-1, y=gi-1;
		merge(x,y);
	}
	rep(i,n) ++cnt[find(i)];
	
	Status t;
	t.l=0;
	rep(i,n) if (cnt[i]) t.a[t.l++]=cnt[i];
	t.MakeUp(), t.Code();
	
	work(t);
	
	printf("%.6f\n", dp[t]);
	
	return 0;
}
