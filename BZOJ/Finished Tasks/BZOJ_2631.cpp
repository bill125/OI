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

const int inf=~0U>>1, maxn=100000+10, maxp=maxn;
const ll MOD=51061;
int n, m;
struct Node {
	ll sz, v, k, c, sum;
	bool rev, root;
	Node *s[2], *p;
	Node () { v=c=sz=sum=0, rev=root=0, k=1; }
	void upd() {
		sz = s[0]->sz + 1 + s[1]->sz;
		sum = (s[0]->sum + v + s[1]->sum) % MOD;
	}
	void sets(Node *t, int d) { s[d] = t, t->p = this; }
	int d() { return p->s[1] == this; }
	void relax() ;
	void revIt() { swap(s[0], s[1]), rev^=1; }
	void addIt(ll x) { (c+=x)%=MOD, (sum+=x*sz)%=MOD, (v+=x)%=MOD; }
	void mulIt(ll x) { (k*=x)%=MOD, (c*=x)%=MOD, (v*=x)%=MOD, (sum*=x)%=MOD; }
}mem[maxp], *C=mem, Tnull, *null=&Tnull, *p[maxn];
Node *mk() {
	C->v=C->sum=0, C->s[0]=C->s[1]=C->p=null;
	return C++;
}
void Node::relax() {
	rep(i,2) if (s[i] != null) {
		if (k != 1) s[i]->mulIt(k);
		if (c) s[i]->addIt(c);
		if (rev) s[i]->revIt();
	}
	k = 1, c = 0, rev = 0;
}

void rot(Node *t) {
	Node *p=t->p;
	p->relax(), t->relax();
	int d=t->d();
	if (p->root) t->p=p->p;
	else p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (p->root) t->root = 1, p->root = 0;
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
	while (x != null) {
		splay(x);
		x->s[1]->root = 1, z->root = 0;
		x->s[1] = z, x->upd();
		z = x, x = x->p;
	}
}

void ChangeRoot(Node *u) {
	Access(u);
	splay(u);
	u->revIt();
}

void Link(Node *u, Node *v) {
	ChangeRoot(u), Access(v);
	u->p=v;
	Access(u);
}

void Cut(Node *u, Node *v) {
	ChangeRoot(u);
	Access(v), splay(u);
	u->s[1] = null, v->p = null, v->root = 1;
	u->upd();
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) p[i]=mk(), p[i]->root=1, p[i]->addIt(1);
	rep(i,n-1) {
		int u=gi-1, v=gi-1;
		Link(p[u], p[v]);
	}
	rep(i,m) {
		scanf("\n");
		char style=getchar();
		if (style == '+') {
			int u=gi-1, v=gi-1;ll c=gi;
			ChangeRoot(p[u]);Access(p[v]);
			splay(p[v]);
			p[v]->addIt(c);
		}
		else if (style == '-') {
			int u=gi-1, v=gi-1;
			Cut(p[u], p[v]);
			u=gi-1, v=gi-1;
			Link(p[u], p[v]);
		}
		else if (style == '*') {
			int u=gi-1, v=gi-1;ll c=gi;
			ChangeRoot(p[u]);Access(p[v]);
			splay(p[v]);
			p[v]->mulIt(c);
		}
		else {
			int u=gi-1, v=gi-1;
			ChangeRoot(p[u]); Access(p[v]);
			splay(p[v]);
			printf("%lld\n", p[v]->sum);
		}
	}
	
	return 0;   
}
