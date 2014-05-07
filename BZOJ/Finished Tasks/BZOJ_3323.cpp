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

const int inf=~0U>>1,maxn=500000+10,maxp=500000+10;
const ll MOD=20130426;
int n;
ll nx;

inline void update(ll &x, ll y) {
	if ((x+=y)>=MOD) x-=MOD;
}
struct Node {
	Node *s[2], *p;
	ll a,c,tagk,tagb,tagc;
	Node () {tagk=1,a=tagb=tagc=0;}
	int d() { return p->s[1]==this; }
	void sets(Node *t,int d) {
		t->p=this, s[d]=t;
	}
	void mulIt(ll x) {
		tagk*=x, tagb*=x, a*=x;
		a%=MOD, tagk%=MOD, tagb%=MOD;
	}
	void upIt(ll x) {
		c+=x, tagc+=x;
	}
	void addIt(ll x) {
		update(tagb,x);
		update(a,x);
	}
	void relax() ;
}Tnull,*null=&Tnull,*root,mem[maxp],*C=mem;
void Node::relax() {
	rep(i,2) if (s[i]!=null) {
		if (tagc)
			s[i]->upIt(tagc);
		if (tagk!=1) 
			s[i]->mulIt(tagk);
		if (tagb) 
			s[i]->addIt(tagb);
	}
	tagk=1, tagb=tagc=0;
}
Node *mk(int c) {
	Node *t=C++;
	t->c=c;
	t->s[0]=t->s[1]=t->p=null;
	return t;
}
void rotate(Node *t) {
	Node *p=t->p;
	p->relax();
	t->relax();
	int d=t->d();
	p->p->sets(t,p->d());
	p->sets(t->s[d^1],d);
	t->sets(p,d^1);
	if (root==p) root=t;
}
void splay(Node *t,Node *top=null) {
	while (t->p!=top)
		if (t->p->p==top)
			rotate(t);
		else {
			(t->d()==t->p->d())?rotate(t->p):rotate(t);
			rotate(t);
		}
}
void print(Node *t) {
	if (t->s[0]!=null) print(t->s[0]);
	if (t->a) 
		printf("%lld*x^%lld\n", t->a, t->c);
	if (t->s[1]!=null) print(t->s[1]);
}
Node *build(int l,int r) {
	if (l==r) return null;
	if (l+1==r) {
		Node *now=mk(l);
		return now;
	}
	int m=(l+r)>>1;
	Node *now=mk(m);
	now->sets(build(l,m),0);
	now->sets(build(m+1,r),1);
	return now;
}
Node *find(int c) {
	for (Node *t=root;;) {
		t->relax();
		if (t->c==c) return t;
		else t=t->s[c>t->c];
	}
}
void mul(int l,int r,ll v) {
	Node *L=find(l-1), *R=find(r+1);
	splay(L), splay(R,L);
	R->s[0]->mulIt(v);
	splay(R->s[0]);
}
void add(int l,int r,ll v) {
	Node *L=find(l-1), *R=find(r+1);
	splay(L), splay(R,L);
	R->s[0]->addIt(v);
	splay(R->s[0]);
}
void Del(Node *t) {
	while (t->s[0]!=null || t->s[1]!=null) {
		if (t->s[0]!=null) rotate(t->s[0]);
		else rotate(t->s[1]);
	}
	
	Node *p=t->p;
	p->sets(null,t->d());
	splay(p);

//	delete t;
	return ;
}
void Add(int c) {
	Node *L=find(c-1), *R=find(c+1);
	splay(L), splay(R,L);
	Node *t=mk(c);
	R->sets(t,0);
}
void mulx(int l,int r) {
	Node *L=find(l-1), *R=find(r+1);
	
	ll a=R->a;
	splay(L), splay(R,L);
	
	R->s[0]->upIt(1);
	Del(R);
	
	Add(l);
	R=find(r+1);
	R->a+=a;
}
ll calc(Node *t,ll x) {
	ll res=0;
	t->relax();
	if (t->s[0]!=null) update(res,calc(t->s[0],x));
	if (t->c>=0) {
		//if (t->a) printf("%lld %lld\n", t->a, nx);
		res+=t->a*nx;res%=MOD;
		nx=(nx*x)%MOD;
	}
	if (t->s[1]!=null) update(res,calc(t->s[1],x));
	return res;
}
int main() {
	setIO("test");
	
	n=gi;
	int p=100000;
	
	root=build(-1,p*2+2);
	//return 0;
	rep(i,n) {
		char c[10];
		int t=gs(c);
		if (c[0]=='m') {
			if (t==3) {
				int l=gi, r=gi;ll v=gi;
				mul(l,r,v);
			}
			else {
				int l=gi, r=gi;
				mulx(l,r);
			}
		}
		else if (c[0]=='a') {
			int l=gi, r=gi;ll v=gi;
			v%=MOD;
			add(l,r,v);
		}
		else {
			ll v=gi;
			nx=1;
			printf("%lld\n", calc(root,v));
		}
	}
	
	return 0;
}
