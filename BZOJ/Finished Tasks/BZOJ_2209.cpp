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

const int inf=~0U>>1, maxn=100000+10, maxp=maxn;
int n,m;
char c[maxn];

struct Node {
	Node *s[2], *p;
	int sz, val;
	int maxL, maxR, minL, minR, sum;
	bool rev, inv;
	Node () ;
	int d() { return p->s[1]==this; }
	void sets(Node *t,int d) { t->p=this, s[d]=t; }
	void ref() ;
	void relax() ;
	void revIt() {
		rev^=1;
		swap(s[0], s[1]);
		swap(maxL, maxR), swap(minL, minR);
	}
	void invIt() {
		inv^=1;
		swap(maxL, minL), swap(maxR, minR);
		maxL=-maxL, minL=-minL, maxR=-maxR, minR=-minR;
		sum=-sum, val=-val;
	}
}Tnull, *null=&Tnull, mem[maxp], *C=mem, *root;
void Node::relax() {
	rep(i,2) if (s[i]!=null) {
		if (rev) s[i]->revIt();
		if (inv) s[i]->invIt();
	}
	rev=inv=0;
}
Node::Node() {
	s[0]=s[1]=p=null;
	maxL=minL=maxR=minR=0;
	sz=val=sum=0;
	rev=inv=0;
}
void Node::ref() {
	maxL=max(s[0]->maxL, s[0]->sum+val+s[1]->maxL);
	minL=min(s[0]->minL, s[0]->sum+val+s[1]->minL);
	maxR=max(s[1]->maxR, s[1]->sum+val+s[0]->maxR);
	minR=min(s[1]->minR, s[1]->sum+val+s[0]->minR);
	sum=s[0]->sum+s[1]->sum+val;
	sz=s[0]->sz+1+s[1]->sz;
}
Node *mk(int v) {
	C->val=v;
	C->ref();
	return C++;
}
void rot(Node *t) {
	Node *p=t->p;
	p->relax();
	t->relax();
	int d=t->d();
	p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (root==p) root=t;
	p->ref();
}
void splay(Node *t, Node *top=null) {
	while (t->p!=top) 
		if (t->p->p==top) rot(t);
		else {
			(t->p->d()==t->d())?(rot(t->p)):(rot(t));
			rot(t);
		}
	t->ref();
}
Node *select(int k) {
	for (Node *t=root;;) {
		t->relax();
		int c=t->s[0]->sz+1;
		if (c==k) return t;
		else if (c<k) k-=c, t=t->s[1];
		else t=t->s[0];
	}
}
Node *get(int l,int r) {
	if (l==1 && r==n) return root;
	else if (l==1) {
		Node *t=select(r+1);splay(t);
		return t->s[0];
	}
	else if (r==n) {
		Node *t=select(l-1);splay(t);
		return t->s[1];
	}
	else {
		Node *L=select(l-1), *R=select(r+1);
		splay(L), splay(R,L);
		return R->s[0];
	}
}
Node *build(int l,int r) {
	if (l==r) return null;
	if (l==r-1) {
		Node *t=mk((c[l]=='(')?(-1):1);
		return t;
	}
	int m=(l+r)>>1;
	Node *t=mk((c[m]=='(')?(-1):1);
	t->sets(build(l,m), 0);
	t->sets(build(m+1,r), 1);
	t->ref();
	return t;
}
void Invert(int l,int r) { Node *t=get(l,r);t->invIt();splay(t); }
void Reverse(int l,int r) { Node *t=get(l,r);t->revIt();splay(t); }
int Query(int l,int r) { Node *t=get(l,r); return (t->maxL+1)/2+(-t->minR+1)/2; }
int main() {
	setIO("test");
	
	n=gi, m=gi;
	scanf("%s", c);
	root=build(0,n);

	rep(i,m) {
		int style=gi, l=gi, r=gi;
		if (style==0) printf("%d\n", Query(l,r));
		else if (style==1) Invert(l,r);
		else Reverse(l,r);
	}
	
	return 0;
}
