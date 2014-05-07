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

const int inf=~0U>>1, maxn=20000+10, maxt=500000+10;
int n, m, Tcnt=0;
Pair a[maxn];
int q[4];
map<int,int> F;
struct Node {
	int L, R, sum;
	void ref() ;
	Node () {}
	Node (int _L,int _R,int _sum) : L(_L), R(_R), sum(_sum) {}
}T[maxt];
int root[maxn], ls[maxt], rs[maxt], key[maxn];
Node operator+(const Node &l, const Node &r) {
	Node t;
	t.L=max(l.L, l.sum+r.L);
	t.R=max(r.R, r.sum+l.R);
	t.sum=l.sum+r.sum;
	return t;
}

bool cmp(int x,int y) { return a[x]<a[y]; }

void build(int l,int r,int &rt) {
	rt=++Tcnt;
	if (l==r) {
		T[rt].L=T[rt].R=T[rt].sum=1;
		return ;
	}
	int m=(l+r)>>1;
	build(l,m,ls[rt]), build(m+1,r,rs[rt]);
	T[rt]=T[ls[rt]]+T[rs[rt]];
}

void modify(int p,int x,int k,int l,int r,int &rt) {
	rt=++Tcnt;
	ls[rt]=ls[p], rs[rt]=rs[p];
	if (l==r) {
		T[rt].L=T[rt].R=T[rt].sum=k;
		return ;
	}
	int m=(l+r)>>1;
	if (x<=m) modify(ls[p], x, k, l, m, ls[rt]);
	else modify(rs[p], x, k, m+1, r, rs[rt]);
	T[rt]=T[ls[rt]]+T[rs[rt]];
}

Node query(int p,int L,int R,int l,int r) {
	if (L>R) return Node(0,0,0);
	if (l==L && R==r) return T[p];
	int m=(l+r)>>1;
	if (L>m) return query(rs[p], L, R, m+1, r);
	else if (R<=m) return query(ls[p], L, R, l, m);
	else return query(ls[p], L, m, l, m)+query(rs[p], m+1, R, m+1, r);
}

bool check(int p,int a,int b,int c,int d) {
	return query(p,a,b,0,n-1).R+query(p,b+1,c-1,0,n-1).sum+query(p,c,d,0,n-1).L>=0;
}
int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) a[i].first=gi, a[i].second=i;
	sort(a, a+n);
	int t;
	build(0, n-1, root[0]);
	For(i,1,n-1) modify(root[i-1], a[i-1].second, -1, 0, n-1, root[i]);
	
	m=gi;
	int ans=0;
	rep(i,m) {
		rep(j,4) q[j]=(gi+ans)%n;
		
		sort(q, q+4);
		int l=-1, r=n;
		while (l+1<r) {
			int m=(l+r)>>1;
			if (check(root[m], q[0], q[1], q[2], q[3])) l=m;
			else r=m;
		}
		printf("%d\n", ans=a[l].first);
	}
	
	return 0;
}
