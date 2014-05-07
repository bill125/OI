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

const int inf=~0U>>1, maxp=100000+10, maxn=100000+10;
int n, m;
char c[maxn];
struct Node {
	Node *s[2], *p;
	int maxL, minL, maxR, minR, sum, key, chg, sz;
	bool inv, rev;
	int d() { return p->s[1]==this; }
	void sets(Node *t, int d) { t->p=this, s[d]=t; }
	void invIt() { 
		inv^=1; 
		swap(maxL, minL), swap(maxR, minR);
		maxL=-maxL, minL=-minL, maxR=-maxR, minR=-minR, sum=-sum, key=-key;
	}
	void revIt() { 
		rev^=1;
		swap(s[0], s[1]);
		swap(maxL, maxR), swap(minL, minR);
	}
	Node ();
	void chgIt(int k) {
		rev=inv=0, key=chg=k;
		if (k==1) maxL=maxR=sum=sz, minL=minR=0;
		else minL=minR=sum=-sz, maxL=maxR=0;
	}
	void relax();
	void ref(); 
}mem[maxp], *C=mem, Tnull, *null=&Tnull, *root;
Node::Node () {
	s[0]=s[1]=p=null;
	maxL=maxR=minL=minR=sum=0;
	inv=rev=0, sz=chg=0;
}
Node *mk(int k) {
	C->key=k;
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
void Node::ref() {
	sz=s[0]->sz+1+s[1]->sz;
	maxL=max(s[0]->maxL, s[0]->sum+key+s[1]->maxL);
	minL=min(s[0]->minL, s[0]->sum+key+s[1]->minL);
	maxR=max(s[1]->maxR, s[1]->sum+key+s[0]->maxR);
	minR=min(s[1]->minR, s[1]->sum+key+s[0]->minR);
	sum=s[0]->sum+s[1]->sum+key;
}
void Node::relax() {
	rep(i,2) if (s[i]!=null) {
		if (chg) s[i]->chgIt(chg);
		if (rev) s[i]->revIt();
		if (inv) s[i]->invIt();
	}
	rev=inv=0, chg=0;
}
void splay(Node *t, Node *top=null) {
	while (t->p!=top) 
		if (t->p->p==top) rot(t); //
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
Node *build(int l,int r) {
	if (l==r) return null;
	if (l+1==r) {
		Node *now=mk((c[l]=='(')?(-1):1);
		return now;
	}
	int m=(l+r)>>1;
	Node *now=mk((c[m]=='(')?(-1):1);
	now->sets(build(l,m), 0);
	now->sets(build(m+1,r), 1);
	now->ref();
	return now;
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

void Change(int l,int r,int k) { Node *t=get(l,r);t->chgIt(k);splay(t); }
void Reverse(int l, int r) { Node *t=get(l,r);t->revIt();splay(t); }
void Invert(int l,int r) { Node *t=get(l,r);t->invIt();splay(t); }
int Query(int l,int r) { Node *t=get(l,r); return (t->maxL+1)/2+(-t->minR+1)/2; }

int main() {
	setIO("test");
	
	n=gi, m=gi;
	scanf("%s", c);
	root=build(0,n);
	rep(i,m) {
		scanf("%s", c);
		int l=gi, r=gi;
		if (c[0]=='R') { char k=getchar(); Change(l,r,(k=='(')?(-1):1); }
		else if (c[0]=='S') Reverse(l,r); 
		else if (c[0]=='I') Invert(l,r); 
		else printf("%d\n",  Query(l,r)); 
	}
	
	return 0;
}
