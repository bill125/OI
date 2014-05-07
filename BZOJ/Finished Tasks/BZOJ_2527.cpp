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

typedef unsigned long long ll;
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

const int inf=~0U>>1, maxn=300000+10, maxT=1000000+10, maxq=maxn, maxm=maxn;
int n,m,q;
int o[maxm], ans[maxn], a[maxn];
ll p[maxn];
bool v[maxn];
vector<int> pos[maxn];
struct StoneFall {
	int l,r;ll c;
}s[maxq];
struct SegTree {
    int h;
    ll a[maxT], add[maxT];
    bool clr[maxT];
    void init(int n) { for (h=1; (1<<h)<n+2; ++h) ; fill(a,0), fill(add,0), fill(clr,0); }
    void upd(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
    void addIt(int x,ll c) { add[x]+=c, a[x]+=c; }
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
    void Add(int x,int y,ll c) {
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
    ll Sum(int x) {
        x+=(1<<h);
        pass(x);
        return a[x];
    }
}T;


void work(int l,int r,int b,int e) {
	if (b>e) return;
	if (l==r) {
		For(i,b,e) ans[a[i]]=l+1;
		return ;
	}
	int mid=(l+r)>>1;
	T.Clr();
	For(i,l,mid) 
		if (s[i].l>s[i].r) T.Add(s[i].l,m,s[i].c), T.Add(1,s[i].r,s[i].c);
		else T.Add(s[i].l,s[i].r,s[i].c);
	
	int lab=b;
	For(_i,b,e) {
		ll now=0;int i=a[_i];
		forv(j,pos[i]) {
			int x=pos[i][j];
			now+=T.Sum(x);
			if (now>=p[i]) break;
		}
		if (now<p[i]) p[i]-=now, v[i]=1;
		else v[i]=0, ++lab;
		//printf("%lld%c", now, (_i==e)?'\n':' ');
	}
	
	int j=lab;
	For(i,b,lab-1) {
		while (j<=e && v[a[j]]) ++j;
		if (v[a[i]]) swap(a[i],a[j]), ++j;
	}
	//return ;
	work(l,mid,b,lab-1);
	work(mid+1,r,lab,e);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) {
		int o=gi-1;
		pos[o].pb(i+1);
	}
	rep(i,n) p[i]=gi, a[i]=i;
	T.init(m);
	q=gi;
	rep(i,q) s[i].l=gi, s[i].r=gi, s[i].c=gi;
	fill(ans,-1);
	
	work(-1,q,0,n-1);
	
	rep(i,n) 
		if (ans[i]==q+1) puts("NIE");
		else printf("%d\n", ans[i]);
	
	return 0;
}
