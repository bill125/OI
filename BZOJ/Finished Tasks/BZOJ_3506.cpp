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

const int inf=~0U>>1, maxn=100000+10, maxp=maxn;
int n;
Pair a[maxn];

struct Node {
	Node *s[2], *p;
	int sz, Minp;
	Pair val, Min;
	bool rev; 
	void sets(Node *t,int d) { t->p=this, s[d]=t; }
	int d() { return p->s[1]==this; }
	void revIt() { 
		rev^=1, swap(s[0],s[1]);
		if (Minp!=2) Minp^=1;
	}
	void upd();
	void relax();
	Node ();
}Tnull, *null=&Tnull, *root, mem[maxp], *C=mem;
Node::Node() { s[0]=s[1]=p=null; sz=0; val.first=Min.first=inf; Minp=2;}
Node *mk(Pair val) {
	C->val=C->Min=val, C->Minp=2, C->sz=1;
	return C++;
}
void Node::upd()	{ 
	sz=s[0]->sz+1+s[1]->sz; 
	Min=val, Minp=2;
	if (s[0]!=null && s[0]->Min<Min) Min=s[0]->Min, Minp=0;
	if (s[1]!=null && s[1]->Min<Min) Min=s[1]->Min, Minp=1;
}
void Node::relax() {
	if (rev) {
		rep(i,2) if (s[i]!=null) s[i]->revIt();
	}
	rev=0;
}
void rot(Node *t) {
	Node *p=t->p;
	p->relax(), t->relax();
	int d=t->d();
	p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (root==p) root=t;
	p->upd();
}
void splay(Node *t,Node *top=null) {
	while (t->p!=top) {
		if (t->p->p==top) rot(t);
		else {
			(t->p->d()==t->d())?rot(t->p):rot(t);
			rot(t);
		}
	}
	t->upd();
}
Node *select(int k) {
	for (Node *t=root;;) {
		t->relax();
		int c=t->s[0]->sz+1;
		if (k==c) return t;
		else if (k>c) k-=c, t=t->s[1];
		else t=t->s[0];
	}
}
Node *get(int l,int r) {
	if (l==1 && r==n) return root;
	else if (l==1) {
		Node *t=select(r+1);
		splay(t);
		return t->s[0];
	}
	else if (r==n) {
		Node *t=select(l-1);
		splay(t);
		return t->s[1];
	}
	else {
		Node *L=select(l-1), *R=select(r+1);
		splay(L), splay(R,L);
		return R->s[0];
	}
}
Node *find(int l,int r) {
	for (Node *t=get(l,r);;) {
		t->relax();
		if (t->Minp==2) return t;
		else t=t->s[t->Minp];
	}
}
Node *build(int l,int r) {
	if (l==r) return null;
	if (l+1==r) {
		Node *now=mk(a[l]);
		return now;
	}
	int m=(l+r)>>1;
	Node *now=mk(a[m]);
	now->sets(build(l,m), 0);
	now->sets(build(m+1,r), 1);
	now->upd();
	return now;
}
void Reverse(int l,int r) {
	Node *x=get(l,r);
	x->revIt();
	splay(x);
}

int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) a[i].first=gi, a[i].second=i;
	//sort(a, a+n);
	root=build(0,n);
	
	For(i,1,n) {
		Node *x=find(i,n);
		splay(x);
		printf("%d%c", x->s[0]->sz+1, (i==n)?'\n':' ');
		int l=i, r=x->s[0]->sz+1;
		Reverse(l, r);
	}
	
	return 0;
}
