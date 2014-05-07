// Author: bill125
// ntr czr
// orz zyx
// orz Mushroom
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
	string in = NAME + ".in",out = NAME + ".out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i], (i==n-1) ? '\n' : ' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1,maxn=10000+10, maxT=400000;
int n,m,cnt=0;
int a[maxn];

//内层 splay
struct Node2 {
	Node2 *s[2], *p;
	int x, sz;
	void sets(Node2 *t, int d) { s[d]=t, t->p=this; }
	int d() { return p->s[1]==this; }
	void upd() { sz=s[0]->sz+1+s[1]->sz; }
	Node2 () { sz=0; }
}Tnull2, *null2=&Tnull2, mem2[maxT], *C2=mem2;
Node2 *mk(int x) {
	C2->x=x, C2->sz=1;
	C2->s[0]=C2->s[1]=C2->p=null2;
	return C2++;
}
void rot(Node2 *t,Node2 *&root) {
	Node2 *p=t->p;
	int d=t->d();
	p->p->sets(t,p->d());
	p->sets(t->s[d^1],d);
	t->sets(p,d^1);
	if (root==p) root=t;
	p->upd();
}
void splay(Node2 *t,Node2 *&root, Node2 *top=null2) {
	while (t->p!=top) 
		if (t->p->p==top)
			rot(t,root);
		else {
			(t->p->d()==t->d())?(rot(t->p,root)):(rot(t,root));
			rot(t,root);
		}
	t->upd();
}
void ins(int x,Node2 *&root) {
	for (Node2 *t=root;;) {
		int d=x>=t->x;
		if (t->s[d]!=null2) t=t->s[d];
		else {
			t->sets(mk(x),d);
			splay(t->s[d],root);
			return ;
		}
	}
}
void del(Node2 *t,Node2 *&root) {
	while (t->s[0]!=null2 || t->s[1]!=null2)
		if (t->s[0]!=null2) rot(t->s[0],root);
		else rot(t->s[1],root);
	Node2 *p=t->p;
	p->sets(null2,t->d());
	splay(p,root);
}
Node2 *mk(int L,int R) {
	Node2 *now=mk(1000000000);
	For(i,L,R) ins(a[i],now);
	return now;
}
Node2 *select(Node2 *t,int x) {
	for (;;) 
		if (t->x==x) return t;
		else if (t->x<x) t=t->s[1];
		else t=t->s[0];
}
void chg(Node2 *&root,int x,int y) {
	Node2 *t=select(root,x);
	del(t,root);
	ins(y,root);
}
int calc(Node2 *t,int x) {
	int res=0;
	for (;t!=null2;) 
		if (t->x<=x) res+=t->s[0]->sz+1, t=t->s[1];
		else t=t->s[0]; 
	return res;
}

//外围 线段树
struct Node1 {
	Node1 *l, *r;
	int L, R;
	Node2 *s;
	Node1();
}Tnull1, *null1=&Tnull1, mem1[maxT], *C1=mem1, *root;
Node1::Node1 () { l=r=null1; }
void visit(Node2 *t) {
	if (t->s[0]!=null2) visit(t->s[0]);
	printf("%d ", t->x);
	if (t->s[1]!=null2) visit(t->s[1]);
}
Node1 *build(int L,int R) {
	Node1 *now=C1++;
	now->L=L, now->R=R;
	now->s=mk(L,R);
	if (L==R) return now;
	int M=(L+R)>>1;
	now->l=build(L,M);
	now->r=build(M+1,R);
	return now;
}
int Count(int L,int R,int x,Node1 *t) {
	int res=0;
	if (t==null1) return res;
	if (L<=t->L && t->R<=R) return calc(t->s,x);
	if (t->L==t->R) return res;
	int M=(t->L+t->R)>>1;
	if (L<=M) res+=Count(L,R,x,t->l);
	if (R>=M+1) res+=Count(L,R,x,t->r);
	return res;
}
void Change(int x,int u,int v,Node1 *t) {
	if (t==null1) return ;
	chg(t->s,u,v);
	if (t->L==t->R) return ;
	int M=(t->L+t->R)>>1;
	if (x<=M) Change(x,u,v,t->l);
	else Change(x,u,v,t->r);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) a[i]=gi;
	root=build(0,n-1);
	
	rep(i,m) {
		scanf("\n");
		char c=getchar();
		if (c=='Q') {
			int l=gi-1, r=gi-1, k=gi;
			int L=-1, R=1000000001;
			while (L+1<R) {
				int M=(L+R)>>1;
				if (Count(l,r,M,root)>=k) R=M;
				else L=M;
			}
			printf("%d\n", R);
		}
		else {
			int x=gi-1, c=gi;
			Change(x,a[x],c,root);
			a[x]=c;
		}
	}
	
	return 0;
}
