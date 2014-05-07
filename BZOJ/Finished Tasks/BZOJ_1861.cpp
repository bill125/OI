//Author: bill125

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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define pb push_back
#define mp make_pair
#define v1 first
#define v2 second
#define gi gI()
#define cut puts("===================")

void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in = NAME + ".in";
	string out = NAME + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
	#endif
}
ll gI() {
	char c=getchar();
	while ((c<'0' || c>'9')&&c!='-') c=getchar();
	ll flag=1,p=0;
	if (c=='-') flag=-1,c=getchar();
	while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();
	return p*flag;
}
int gs(char *C) {
	char c=getchar();
	while (c==' ' || c=='\n') c=getchar();
	int l=0;
	while (c!=' ' && c!='\n') C[l++]=c,c=getchar();
	C[l]=0;
	return l;
}

template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i], (i==n-1) ? '\n' : ' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1,maxn=80000+10;
int n,m;
int a[maxn];

struct Node {
	Node *s[2], *p;
	int sz, id;
	void upd() ;
	void sets(Node *t,int d) {
		s[d]=t, t->p=this;
	}
	int d() {return p->s[1]==this;}
	Node () ;
}*b[maxn], *root, Tnull, *null=&Tnull;
void Node::upd() {
	sz=s[0]->sz+1+s[1]->sz;
}
Node::Node () { sz=0, s[0]=s[1]=p=null; }

void rotate(Node *t) {
	Node *p=t->p;
	int d=t->d();
	p->p->sets(t,p->d());
	p->sets(t->s[d^1],d);
	t->sets(p,d^1);
	if (root==p) root=t;
	p->upd();
}

void splay(Node *t,Node *top=null) {
	while (t->p!=top) 
		if (t->p->p==top)
			rotate(t);
		else {
			(t->p->d()==t->d())?rotate(t->p):rotate(t);
			rotate(t);
		}
	t->upd();
}

Node *build(int L,int R,int a[]) {
	if (L==R) return null;
	if (L+1==R) {
		Node *T=new Node;
		T->sz=1, T->id=a[L];
		T->s[0]=T->s[1]=T->p=null;
		b[a[L]]=T;
		return T;
	}
	int M=(L+R)>>1;
	Node *T=new Node;
	T->s[0]=build(L,M,a);
	T->s[1]=build(M+1,R,a);
	T->s[0]->p=T, T->s[1]->p=T;
	T->id=a[M], b[a[M]]=T;
	T->upd();
	return T;
}

void Del(Node *t) {
	while (t->s[0]!=null || t->s[1]!=null)
		if (t->s[0]!=null) rotate(t->s[0]);
		else rotate(t->s[1]);
	Node *p=t->p;
	p->sets(null,t->d());
	splay(p);
}

Node *select(int k) {
	for (Node *t=root;;) {
		int c=t->s[0]->sz+1;
		if (k==c) return t;
		else if (k<c) t=t->s[0];
		else k-=c, t=t->s[1];
	}
}

void Top(Node *x) {
	Del(x);
	Node *t=select(1);
	splay(t);
	t->sets(x,0);
	splay(x);
}

void Bottom(Node *x) {
	Del(x);
	Node *t=select(n-1);
	splay(t);
	t->sets(x,1);
	splay(x);
}

int getsz(Node *t) {
	int res=t->s[0]->sz+1;
	for (;t!=root;) {
		if (t->d()) res+=t->p->s[0]->sz+1;
		t=t->p;
	}
	return res;
}

void Put(Node *t,int pos) {
	Del(t);
	Node *a=select(pos-1), *b=select(pos);
	splay(a), splay(b,a);
	b->sets(t,0);
	splay(t);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) a[i]=gi-1;
	root=build(0,n,a);
	
	rep(i,m) {
		char style[10];
		scanf("%s", style);
		if (style[0]=='T') {
			int x=gi-1;
			Top(b[x]);
		}
		else if (style[0]=='B') {
			int x=gi-1;
			Bottom(b[x]);
		}
		else if (style[0]=='I') {
			int x=gi-1, t=gi;
			int pos=getsz(b[x])+t;
			if (pos==1) Top(b[x]);
			else if (pos==n) Bottom(b[x]);
			else Put(b[x],pos);
		}
		else if (style[0]=='A') {
			int x=gi-1;
			printf("%d\n", getsz(b[x])-1); 
		}
		else if (style[0]=='Q') {
			int x=gi;
			printf("%d\n", select(x)->id+1);
		}
	}
	
	return 0;
}
