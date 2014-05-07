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

const int inf=~0U>>1, maxn=300000+10, maxp=maxn;
int n, m;
bool flag=0;
struct Node {
	Node *s[2], *p;
	int sz, v, sum, i;
	bool root, rev;
	void revIt() { rev^=1, swap(s[0], s[1]); }
	void upd() { sz = s[0]->sz + 1 + s[1]->sz; sum = s[0]->sum ^ v ^ s[1]->sum; }
	void sets(Node *t, int d) { s[d]=t, t->p=this; }
	int d() { return p->s[1]==this; }
	void relax();
}Tnull, *null=&Tnull, mem[maxp], *C=mem, *p[maxn];
void Node::relax() {
	if (rev) {
		rep(i,2) if (s[i]!=null) s[i]->revIt();
		rev=0;
	}
}

Node *mk(int v) {
	C->v=C->sum=v, C->s[0]=C->s[1]=C->p=null;
	C->rev=0;
	return C++;
}

void rot(Node *t) {
	Node *p=t->p;
	p->relax(), t->relax();
	int d=t->d();
	if (p->root) t->p=p->p;
	else p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (p->root) t->root=1, p->root=0;
	p->upd();
}

void splay(Node *t) {
	t->relax();
	while (!t->root) 
		if (t->p->root) rot(t);
		else {
			(t->p->d() == t->d()) ? rot(t->p) : rot(t);
			rot(t);
		}
	t->upd();
}

void Access(Node *x) {
	Node *z=null;
	while (x!=null) {
		splay(x);
		x->s[1]->root=1, z->root=0;
		x->sets(z, 1), x->upd();
		z=x, x=x->p;
	}
}

Node *FindRoot(Node *u) {
	Access(u), splay(u);
	for (;u->s[0]!=null;u->relax(), u=u->s[0]) ;
	splay(u);
	return u;
}

void ChangeRoot(Node* u) {
	Access(u);
	splay(u);
	u->revIt();
}

void Link(Node *u,Node *v) {
	Access(v), ChangeRoot(u);
	u->p=v;
	Access(u);
}

void Cut(Node *u,Node *v) {
	ChangeRoot(u);
	if (v->p != u) return ;
	Access(v), splay(u);
	u->s[1] = null, v->p=null, v->root=1, u->upd();
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) {
		int v=gi;
		p[i]=mk(v), p[i]->root=1, p[i]->i=i+1;
	}
	rep(i,m) {
		int style=gi, x=gi-1, y=gi-1;
		if (style == 0) {
			ChangeRoot(p[x]), Access(p[y]), splay(p[y]);
			printf("%d\n", p[y]->s[0]->sum ^ p[y]->v);
		}
		else if (style == 1) {
			if (FindRoot(p[x]) == FindRoot(p[y])) continue;
			
			Link(p[x], p[y]);
		}
		else if (style == 2) {
			if (FindRoot(p[x]) != FindRoot(p[y])) continue;
			Cut(p[x], p[y]);
		}
		else {
			p[x]->v = ++y;
			splay(p[x]);
		}
	}

	return 0;   
}
