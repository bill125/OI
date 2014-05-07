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

const int inf=~0U>>1, maxn=300000+10;
int n;
int delta;
map<int, int> f;

struct Node {
	Node *s[2], *p;
	int i, v, maxv, add, sz;
	int d() { return p->s[1]==this; }
	void sets(Node *t, int d) { s[d]=t, t->p=this; }
	void addIt(int k) { v+=k, maxv+=k, add+=k; }
	void relax();
	void upd();
	Node() ;
}*p[maxn], Tnull, *null=&Tnull, *root;
Node::Node() { v=maxv=-100000000, add=sz=0, s[0]=s[1]=p=null; }

void Node::upd() { maxv=max(v, max(s[0]->maxv, s[1]->maxv)); sz=s[0]->sz + 1 + s[1]->sz; }
void Node::relax() {
	rep(i,2) if (s[i]!=null)
		s[i]->addIt(add);
	add=0;
}
void rot(Node *t) {
	Node *p=t->p;
	p->relax(), t->relax();
	int d=t->d();
	p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	p->upd();
}
void splay(Node *t, Node *top=null) {
	t->relax();
	while (t->p!=top) 
		if (t->p->p==top) rot(t);
		else {
			(t->p->d() == t->d())?rot(t->p):rot(t);
			rot(t);
		}
	t->upd();
}

Node* mk(int k) {
	Node *c=new Node;
	c->v=k, c->sz=1;
	c->upd();
	return c;
}

Node *Insert(int v,Node *t) {
	for (;t!=null;) {
		t->relax();
		int d = v>t->v;
		if (t->s[d]==null) {
			Node *c=mk(v);
			t->sets(c, d);
			splay(c);
			return c;
		}
		else t=t->s[d];
	}
}

void merge(Node *x) {
	x->relax();
	if (x->s[0]!=null) merge(x->s[0]);
	int i=x->i;
	root=p[i]=Insert(x->v, root), p[i]->i=i;
	if (x->s[1]!=null) merge(x->s[1]);
}

inline void del(int x) {  if (--f[x]==0) f.erase(x); }
inline void add(int x) {  if (f.count(x)) ++f[x]; else f[x]=1; }

int main() {
	setIO("test");
	
	n=gi;
	delta=0;
	rep(i,n) { int k=gi; p[i]=mk(k);p[i]->i=i;add(k); }
	
	
	for (int m=gi; m--; ) {
		char c[4];gs(c);
		if (c[0]=='U') {
			int x=gi-1, y=gi-1;
			splay(p[x]), splay(p[y]);
			if (p[x]->p !=null || x==y) continue;
			del(p[x]->maxv), del(p[y]->maxv);
			if (p[x]->sz > p[y]->sz) swap(x, y);
			root=p[y]; merge(p[x]);
			splay(p[y]);
			add(p[y]->maxv);
		}
		else if (c[0]=='A') 
			if (c[1]=='1') {
				int x=gi-1, v=gi;
				splay(p[x]), del(p[x]->maxv);
				p[x]->v+=v, p[x]->upd(); add(p[x]->maxv);
			}
			else if (c[1]=='2') {
				int x=gi-1, v=gi;
				splay(p[x]), del(p[x]->maxv);
				p[x]->addIt(v), add(p[x]->maxv);
			}
			else {
				int v=gi;
				delta+=v;
			}
		else 
			if (c[1]=='1') {
				int x=gi-1;splay(p[x]);
				printf("%d\n", p[x]->v+delta);
			}
			else if (c[1]=='2') {
				int x=gi-1;splay(p[x]);
				printf("%d\n", p[x]->maxv+delta);
			}
			else {
				map<int,int>::iterator it=f.end();--it;
				printf("%d\n", it->first+delta);
			}
	}
	
	return 0;   
}
