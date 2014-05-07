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

const int inf=~0U>>1,maxn=50000+10,maxm=maxn;
int n,m,tag=0;
int style[maxm],l[maxm],r[maxm],c[maxm],key[maxm];
map<int,int> Index;

struct SgTree{
	SgTree *l, *r;
	int L, R, v, tag;
	SgTree ();
	void add(int, int) ;
	int sum(int ,int) ;
	void refresh() ;
	void relax() ;
	void tagIt(int) ;
}Tnull, *null=&Tnull;
SgTree::SgTree () {
	l=r=null,v=tag=0;
}
SgTree *mk(int L,int R) {
	SgTree *C=new SgTree;
	C->L=L, C->R=R;
	return C;
}
void SgTree::tagIt(int x) {
	tag+=x, v+=(R-L+1)*x;
}
void SgTree::refresh() {
	v=l->v+r->v;
}
void SgTree::relax() {
	if (tag) {
		l->tag+=tag,r->tag+=tag;
		l->v+=(l->R-l->L+1)*tag,r->v+=(r->R-r->L+1)*tag;
		tag=0;
	}
}
void SgTree::add(int Left,int Right) {
	if (L==Left&&R==Right) {
		tagIt(1);
		return ;
	}
	int M=(L+R)>>1;
	if (l==null) l=mk(L,M);
	if (r==null) r=mk(M+1,R);
	relax();
	if (M>=Left) l->add(Left,min(Right,M));
	if (M<Right) r->add(max(M+1,Left),Right);
	refresh();
}

int SgTree::sum(int Left,int Right) {
	if (Left==L && Right==R) return v;
	int res=0;
	int M=(L+R)>>1;
	if (l==null) l=mk(L,M);
	if (r==null) r=mk(M+1,R);
	relax();
	if (M>=Left) res+=l->sum(Left,min(M,Right));
	if (M<Right) res+=r->sum(max(Left,M+1),Right);
	return res;
}

struct VTree{
	VTree *l, *r;
	int L, R;
	SgTree *v;
	VTree ();
	void add(int, int, int) ;
	int ask(int, int, int) ;
}VTnull, *Vnull=&VTnull, *root;
VTree::VTree () {
	l=r=Vnull,v=mk(1,n);
}
VTree *Vmk(int L,int R) {
	VTree *C=new VTree;
	C->L=L, C->R=R;
	return C;
}
void VTree::add(int x,int Left,int Right) {
	v->add(Left,Right);
	if (L==x&&R==x) return ;
	int M=(L+R)>>1;
	if (M>=x) {
		if (l==Vnull) l=Vmk(L,M);
		l->add(x,Left,Right);
	}
	else {
		if (r==Vnull) r=Vmk(M+1,R);
		r->add(x,Left,Right);
	}
}
int VTree::ask(int c,int Left,int Right) {
	if (L==R) return L;
	if (l!=Vnull) {
		int t=l->v->sum(Left,Right);
		if (c<=t) return l->ask(c,Left,Right);
		else return r->ask(c-t,Left,Right);
	}
	else return r->ask(c,Left,Right);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) {
		style[i]=gi, l[i]=gi, r[i]=gi, c[i]=gi;
		if (style[i]==1) Index[c[i]]=1;
	}
	Index[0]=1;
	tag=0;
	ForV(i,Index) i->v2=++tag;
	ForV(i,Index) {
		i->v2=tag+1-i->v2;
		key[i->v2]=i->v1;
	}
	root=Vmk(1,tag);
	
	rep(i,m) {
		if (style[i]==1) root->add(Index[c[i]],l[i],r[i]);
		else printf("%d\n", key[root->ask(c[i],l[i],r[i])]);
	}
	
	return 0;
}
