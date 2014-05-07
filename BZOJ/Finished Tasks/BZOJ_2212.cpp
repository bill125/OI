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

const int inf=~0U>>1, maxn=200000+10, maxp=maxn;
int n;
ll delta,ans=0;
struct Node {
	int val; ll sz;
	Node *s[2], *p;
	void sets(Node *t,int d) { t->p=this, s[d]=t; }
	int d() { return p->s[1]==this; }
	void upd() { sz=s[0]->sz+s[1]->sz+1; }
	Node () ;
}Tnull, *null=&Tnull, mem[maxp], *C=mem, *root;
Node::Node() { s[0]=s[1]=p=null; }
Node *mk(int k) {
	C->sz=1, C->val=k;
	return C++;
}
void rot(Node *t) {
	Node *p=t->p;
	int d=t->d();
	p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	p->upd();
}
void splay(Node *t, Node *top=null) {
	while (t->p!=top)
		if (t->p->p==top) rot(t);
		else {
			(t->p->d()==t->d())?rot(t->p):rot(t);
			rot(t);
		}
	t->upd();
}

void Insert(Node *x) {
	for (Node *t=root;;) {
		int k=x->val>t->val;
		if (t->s[k]==null) {
			t->sets(x, k);
			return ;
		}
		else t=t->s[k];	
	}
}

void merge(Node *x) {
	if (x==null) return ;
	Node *s0=x->s[0], *s1=x->s[1];
	x->s[0]=x->s[1]=x->p=null;
	merge(s0);
	Insert(x);
	splay(x);
	delta+=x->s[1]->sz;
	root=x;
	merge(s1);
}

Node* work() {
	ll k=gi;
	if (k!=0) return mk(k);
	
	Node *l=work(), *r=work();
	ll s1=l->sz, s2=r->sz;
	splay(l), splay(r);
	
	if (l->sz<r->sz) swap(l, r);
	root=l, delta=0;
	merge(r);
	ans+=min(delta, s1*s2-delta);
	
	return root;
}

int main() {
	setIO("test");
	
	n=gi;n=1;
	work();	
	printf("%lld\n", ans);
	
	return 0;
}
