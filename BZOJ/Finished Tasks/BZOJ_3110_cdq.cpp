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

const int inf=~0U>>1, maxn=50000+10, maxm=maxn, maxT=200000+10;
int n,m;
int ans[maxm];
bool v[maxm];
struct Query {
	int l,r,style,c,i;
	bool operator<(const Query& a) const {
		return i<a.i;
	}
}q[maxm];

struct SegTree {
	int h;
	int a[maxT], add[maxT];
	bool clr[maxT];
	void init(int n) { for (h=1; (1<<h)<n+2; ++h) ; fill(a,0), fill(add,0), fill(clr,0); }
	void upd(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
	void addIt(int x,int c) { add[x]+=c, a[x]+=c; }
	void relax(int x) {
		if (clr[x]) {
			clrIt(x<<1), clrIt((x<<1)+1);
			clr[x]=0;
		}
		if (add[x]) {
			addIt(x<<1,add[x]>>1);
			addIt((x<<1)+1, add[x]>>1);
			add[x]=0;
		}
	}
	void clrIt(int x) { a[x]=add[x]=0,clr[x]=1; }
	void pass(int x) { repD(i,h) relax(x>>(i+1)); }
	void ref(int x) { for (x>>=1; x; x>>=1) upd(x); }
	void Clr() { clrIt(1); }
	void Add(int x,int y,int c) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass(l), pass(r);
		while (l+1<r) {
			if (!(l&1)) addIt(l^1,c);
			if (r&1) addIt(r^1,c);
			l>>=1, r>>=1, c<<=1;
		}
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		ref(l), ref(r);
	}
	int Sum(int x,int y) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1, res=0;
		pass(l), pass(r);
		while (l+1<r) {
			if (!(l&1)) res+=a[l^1];
			if (r&1) res+=a[r^1];
			l>>=1, r>>=1;
		}
		return res;
	}
}T;

void work(int l,int r,int b,int e) {
	if (l==r) {
		//printf("%d\n", l);
		For(i,b,e) if (q[i].style==2) ans[q[i].i]=l;
		return ;
	}
	if (b>e) return ;
	sort(q+b, q+e+1);
	int m=(l+r+1)>>1, j=b;
	T.Clr();
	//printf("%d\n", m);
	For(i,b,e) {
		if (q[i].style==1) {
			if (q[i].c>=m) T.Add(q[i].l,q[i].r,1), v[i]=1;
			else v[i]=0;
		}
		else {
			int t=T.Sum(q[i].l,q[i].r);
			if (t>=q[i].c) v[i]=1;
			else q[i].c-=t, v[i]=0;	
		}
		j+=!v[i];
	}
	int t=j-1;
	if (j!=b) {
		For(i,b,t) {
			while (j<=e && v[j]) ++j;
			if (v[i]) swap(q[i],q[j]), swap(v[i], v[j]), ++j;
		}
	}
	work(l,m-1,b,t);
	work(m,r,t+1,e);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) q[i].style=gi, q[i].l=gi, q[i].r=gi, q[i].c=gi, q[i].i=i;
	fill(ans,128);
	
	T.init(n);
	work(-n,n,0,m-1);
	
	rep(i,m) if (ans[i]>=-n) printf("%d\n", ans[i]);
	
	return 0;
}
