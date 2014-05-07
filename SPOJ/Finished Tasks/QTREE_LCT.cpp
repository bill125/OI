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
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n' && c!=EOF) C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=10000+10, maxe=maxn<<1;
int n, cnt;
int a[maxn], b[maxn], c[maxn];
int q[maxn], num[maxn];

struct Edge {
	int y, c;
	Edge *next;
}*h[maxn], mem[maxe], *E=mem;

void Add_Edge(int x,int y,int c) { E->y=y, E->c=c, E->next=h[x], h[x]=E++; }

struct Node {
	Node *p, *s[2];
	int sz, v, maxv, i;
	bool root, rev;
	Node ();
	void sets(Node *t, int d) { t->p=this, s[d]=t; }
	int d() { return p->s[1]==this; }
	void upd() { sz=s[0]->sz+1+s[1]->sz; maxv=max(max(s[0]->maxv, s[1]->maxv),v); }
	void relax() ;
}Tnull, *null=&Tnull, memN[maxn], *C=memN, *p[maxn];
Node::Node() { p=s[0]=s[1]=null; sz=0, root=rev=0; }

void rot(Node *t) {
	Node *p=t->p;
	int d=t->d();
	if (!p->root) p->p->sets(t, p->d());
	else t->p=p->p;
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (p->root) p->root=0, t->root=1;
	p->upd();
}

void splay(Node *t) {
	while (!t->root) 
		if (t->p->root) rot(t);
		else {
			(t->p->d() == t->d()) ? rot(t->p) : rot(t);
			rot(t);
		}
	t->upd();
}

Node *mk() {
	C->s[0]=C->s[1]=C->p=null, C->sz=1, C->v=C->maxv=0;
	return C++;
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

pair<Node*, Node*> Access2(Node *x) {
	Node *z=null;
	for (;;) {
		splay(x);
		if (x->p == null) return mp(z, x);
		x->s[1]->root=1, z->root=0;
		x->sets(z, 1), x->upd();
		z=x, x=x->p;
	}
}

int main() {
	setIO("test");
	
	for (int Td=gi; Td--; ) {
		
	E=mem, C=memN, fill(h, 0);
	
	n=gi;
	rep(i,n-1) {
		a[i]=gi-1, b[i]=gi-1, c[i]=gi;
		Add_Edge(a[i], b[i], c[i]);
		Add_Edge(b[i], a[i], c[i]);
	}
	
	null->i=0;
	rep(i,n) p[i]=mk(), p[i]->root=1, p[i]->i=i+1;
	int r=1;q[0]=0, p[0]->v=0, p[0]->p=null;
	rep(i,r) {int x=q[i];
		ForE(e,x) {int y=e->y;
			if (p[y]==p[x]->p) continue;
			q[r++]=y, p[y]->p=p[x], p[y]->v=p[y]->maxv=e->c;                                                                                                                                                         
		}
	}
	rep(i,n-1) num[i] = (p[a[i]]->p==p[b[i]]) ? a[i] : b[i];
	
	char c[10];
	while (gs(c)) {
		if (c[0] == 'Q') {
			int x=gi-1, y=gi-1, ans=0;
			
			Access(p[x]);
			pair<Node*, Node*> t=Access2(p[y]);
			
			Node *z = t.first, *c = t.second;
			if (z != null) splay(z);
			ans = max(z->maxv, c->s[1]->maxv);
			printf("%d\n", ans);
		}
		else if (c[0] == 'C') {
			int x=gi-1, v=gi;
			x=num[x], p[x]->v=v;
			splay(p[x]);
		}
		else break;
	}
	
	}
	
	return 0;   
}
