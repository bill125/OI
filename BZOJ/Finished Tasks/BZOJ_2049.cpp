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
#include <cmath>

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

const int inf=~0U>>1, maxn=10000+10, maxp=maxn;
int n, m;
struct Node {
	Node *p, *s[2];
	bool root, rev;
	Node ();
	void relax() ;
	int d() { return p->s[1]==this; }
	void revIt() { rev^=1, swap(s[0], s[1]); }
	void sets(Node *t, int d) { s[d]=t, t->p=this; }
}Tnull, *null=&Tnull, *p[maxn], mem[maxp], *C=mem;
Node::Node() { p=s[0]=s[1]=null; rev=root=0; }
void Node::relax() {
	rep(i,2) if (s[i] != null) {
		if (rev) s[i]->revIt();
	}
	rev=0;
}
Node *mk() { return C++; }
void rot(Node *t) {
	Node *p=t->p;
	p->relax(), t->relax();
	int d=t->d();
	if (p->root) t->p=p->p;
	else p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (p->root) t->root=1, p->root=0;
}
void splay(Node *t) {
	t->relax();
	while (!t->root) 
		if (t->p->root) rot(t);
		else {
			(t->d() == t->p->d()) ? rot(t->p) : rot(t);
			rot(t);
		}
}
void Access(Node *x) {
	Node *z=null;
	while (x!=null) {
		splay(x);
		x->s[1]->root = 1, z->root = 0;
		x->s[1] = z;
		z = x, x = x->p;
	}
}
void ChangeRoot(Node *x) {
	Access(x);
	splay(x);
	x->revIt();
}
void Link(Node *u,Node *v) {
	ChangeRoot(u), Access(v), splay(v);
	u->p = v;
}
void Cut(Node *u,Node *v) {
	ChangeRoot(u), Access(v), splay(u);
	v->p = null, v->root = 1, u->s[1] = null;
}
Node *FindRoot(Node *x) {
	for (Access(x), splay(x); x->s[0] != null; x = x->s[0]) ;
	return x;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) p[i] = mk(), p[i]->root = 1;
	
	char c[10];
	rep(i,m) {
		scanf("%s", c);
		int x=gi-1, y=gi-1;
		if (c[0] == 'Q') {
			ChangeRoot(p[x]);
			Access(p[y]);
			if (FindRoot(p[y]) == p[x]) puts("Yes");
			else puts("No");
		}
		else if (c[0] == 'C') {
			Link(p[x], p[y]);
		}
		else {
			Cut(p[x], p[y]);
		}
	}
	
	return 0;   
}
