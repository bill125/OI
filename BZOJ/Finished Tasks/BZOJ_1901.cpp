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
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=10000+10;
int n, m;
int a[maxn];
struct Node {
	Node *s[2];
	int l, r, sum;
	Node ();
}Tnull, *null=&Tnull, *root[maxn], *qx[maxn], *qy[maxn];
Node::Node() { s[0]=s[1]=null; sum=0; }

inline bool Access(Node *t, int d) {
	if (t->l+1==t->r) return 0;
	if (t->s[d]!=null) return 1;
	int m=(t->l+t->r)>>1;
	int l=(d==0)?t->l:m, r=(d==0)?m:t->r;
	if (l==r) return 0;
	t->s[d]=new Node;
	t->s[d]->l=l, t->s[d]->r=r;
	return 1;
}

void Insert(Node *t, int k) {
	++t->sum;
	int m=(t->l+t->r)>>1;
	if (k<m) {
		if (Access(t, 0)) Insert(t->s[0], k);
	}
	else {
		if (Access(t, 1)) Insert(t->s[1], k);
	}
}
void Delete(Node *t, int k) {
	if (t==null) return ;
	--t->sum;
	int m=(t->l+t->r)>>1;
	if (k<m) Delete(t->s[0], k);
	else Delete(t->s[1], k);
}

void add(int x,int k) { for (;x<=n;x+=lowbit(x)) Insert(root[x], k); }
void chg(int x,int k) { int t=a[x]; for (;x<=n;x+=lowbit(x)) Delete(root[x], t), Insert(root[x], k); }
int query(int l,int r,int k) {
	int lx=0, ly=0;
	for (int x=l-1; x; x-=lowbit(x)) qx[lx++]=root[x];
	for (int x=r  ; x; x-=lowbit(x)) qy[ly++]=root[x];
	l=-1, r=1000000000+1;
	int cntx, cnty, d;
	while (l+1<r) {
		int m=(l+r)>>1;
		cntx=0, cnty=0;
		rep(i,lx) cntx+=qx[i]->s[0]->sum;
		rep(i,ly) cnty+=qy[i]->s[0]->sum;
		if (cnty-cntx<k) k-=cnty-cntx, l=m, d=1;
		else r=m, d=0;
		rep(i,lx) qx[i]=qx[i]->s[d];
		rep(i,ly) qy[i]=qy[i]->s[d];
	}
	return l;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	For(i,1,n) root[i]=new Node, root[i]->l=-1, root[i]->r=1000000000+1;
	
	For(i,1,n) a[i]=gi, add(i, a[i]);
	
	rep(i,m) {
		scanf("\n");
		char style=getchar();
		if (style=='Q') {
			int l=gi, r=gi, k=gi;
			printf("%d\n", query(l, r, k));
		}
		else {
			int x=gi, k=gi;
			chg(x, k);
			a[x]=k;
		}
	}
	
	return 0;
}
