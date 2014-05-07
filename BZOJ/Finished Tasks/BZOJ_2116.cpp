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
typedef pair<ll,ll> Pair;
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

const int inf=~0U>>1,maxT=300000+10,maxn=100000+10,maxp=700000+10;
int n, q, tot=0, cnt=0;
bool flag=0;
ll a[maxn];
struct Segment_Tree {
	int h;
	ll a[maxT],sum[maxT],sum2[maxT],maxa[maxT];
	void init(int n, ll o[]) {
		for (h=1; (1<<h)<n+2; ++h) ;
		fill(sum,0), fill(a,0), fill(maxa,128), fill(sum2,0);
		rep(i,n) a[i+(1<<h)+1]=sum2[i+(1<<h)+1]=maxa[i+(1<<h)+1]=o[i], sum[i+(1<<h)+1]=(o[i]>0)?o[i]:0;
		repD(i,(1<<h)) upd(i);
	}
	void upd(int u) {
		int x=u<<1, y=x+1;
		sum[u]=sum[x]+sum[y];
		sum2[u]=sum2[x]+sum2[y];
		maxa[u]=max(maxa[x], maxa[y]);
	}
	void refresh(int u) {for (u>>=1;u;u>>=1) upd(u);}
	void Add(int u,ll c) {
		u+=(1<<h);
		a[u]+=c;
		sum[u]=(a[u]>0)?a[u]:0;
		sum2[u]=a[u];
		maxa[u]=a[u];
		refresh(u);
	}
	ll Ask(int x) {
		x+=(1<<h);
		return a[x];
	}
	Pair Ask(int l,int r) {
		l+=(1<<h)-1, r+=(1<<h)+1;
		ll s=0,m=-inf;
		while (l+1<r) {
			if (!(l&1)) {
				s+=sum2[l^1];
				m=max(m,maxa[l^1]);
			}
			if (r&1) {
				s+=sum2[r^1];
				m=max(m,maxa[r^1]);
			}
			l>>=1, r>>=1;
		}
		return mp(s,m);
	}
	ll Sum() {return sum[1];}
}T;
struct Node {
	Node *s[2], *p;
	int l,r,sz;
	ll v,sum;
	Node () {sz=0;}
	void rotate () ;
	int d() {return this==p->s[1];}
	void sets(Node *t,int d) {
		t->p=this, s[d]=t;
	}
	void upd() ;
}mem[maxp], *C, *root, Tnull, *null=&Tnull;
map<int,Node*> lab;
void Node::upd() {
	sum=v, sz=1;
	rep(i,2) if (s[i]!=null) {
		sum+=s[i]->sum;
		sz+=s[i]->sz;
	}
}
Node *mk(ll v) {
	++cnt;
	C->v=v, C->s[0]=C->s[1]=C->p=null;
	return C++;
}
void rotate(Node *t) {
	Node *p=t->p;
	int d=t->d();
	p->p->sets(t,p->d());
	p->sets(t->s[d^1],d);
	t->sets(p,d^1);
	p->upd();
	if (root==p) root=t;
}
void splay(Node *t,Node *top=null) {
	while (t->p!=top) 
		if (t->p->p==top)
			rotate(t);
		else {
			(t->p->d()==t->d())?rotate(t->p):rotate(t);
			rotate(t);
		}
	t->upd();
}
int getsz(Node *x) {
	int res=x->s[0]->sz+1;
	for (;x!=root;x=x->p) 
		if (x->d()) 
			res+=x->p->s[0]->sz+1;
	return res;
}
Node *find(ll v) {
	Node *x, *res=null;
	for (x=root;;) {
		int d=x->v>v;
		if (x->v>v) res=x; 
		if (x->s[d]!=null) x=x->s[d];
		else break;
	}
	return (res==null)?x:res;
}
Node *select(int k) {
	for (Node *x=root;;) {
		int t=x->s[0]->sz+1;
		if (k==t) return x;
		else if (k>t) k-=t, x=x->s[1];
		else x=x->s[0];
	}
}
void addSeg(int l,int r) {
	++tot;
	ll v;
	if (l==0 || r==n) v=0;
	else {
		Pair t=T.Ask(l,r);
		v=t.second-t.first;
	}
	Node *V=mk(v);
	
	V->l=l, V->r=r;
	if (root==null) root=V;
	else {
		Node *x=find(v);
		splay(x);
		if (x->v<v) x->sets(V,0);
		else if (x->s[1]==null) x->sets(V,1);
		else {
			int sz=getsz(x)+1;
			Node *y=select(sz);	
			splay(y,x);
			y->sets(V,0);
		}
	}
	splay(V);
	lab[l]=V;
}
void deleteSeg(int l) {
	--tot;
	Node *x=lab[l];
	for (;x->s[0]!=null || x->s[1]!=null;) {
		int d=(x->s[0]==null)?1:0;
		rotate(x->s[d]);
	}
	
	Node *p=x->p;
	p->sets(null,x->d());
		
	if (p!=null) splay(p);
	lab.erase(l);
}
int Ask(ll s) {
	int res=0;
	if (s==0) return 0;
	for (Node *x=root;x!=null;) {
		ll t=s-x->s[0]->sum;
		if (t<=0) x=x->s[0];
		else {
			res+=x->s[0]->sz+1, t-=x->v;
			if (t<=0) return res;
			else x=x->s[1], s=t;
		}
	}
	return -1;
}
void Add(int x,ll c) {
	ll v1=T.Ask(x);
	T.Add(x,c);
	ll v2=v1+c;
	if (v1>0) {
		if (v2<0) {
			int v2=lab.upper_bound(x)->first;		
			//if (flag) printf("%d\n", lab.count(n));
			//if (flag) printf("%d %d\n", v2, x);
			Node *n2=lab[v2];			
			map<int,Node*>::iterator it=lab.find(v2);
			--it;
			Node *n1=it->second;
			
			int l=x, r=x;
			if (n1->r+1==l) l=n1->l, deleteSeg(n1->l);
			if (flag) {
			//	printf("%lld\n", n2->v);
				return ;
			}
			if (r+1==n2->l) r=n2->r, deleteSeg(n2->l);
			
			addSeg(l,r);
		}
	}
	else 
		if (v2>0) {
			map<int,Node*>::iterator it=lab.lower_bound(x);
			--it;
			Node *now=it->second;
			int l=now->l, r=now->r;
			deleteSeg(l);
			if (l<=x-1) addSeg(l,x-1);
			if (x+1<=r) addSeg(x+1,r);
		}
		else {
			map<int,Node*>::iterator it=lab.upper_bound(x);
			--it;
			Node *v1=it->second;int l=v1->l, r=v1->r;
			deleteSeg(l);
			addSeg(l,r);
		}
}

void visit(Node *t) {
	if (t->s[0]!=null) visit(t->s[0]);
	printf("%lld\n", t->v);
	if (t->s[1]!=null) visit(t->s[1]);
}

int main() {
	setIO("test");
	
	for (int Td=gi; Td--; ) {
		n=gi, q=gi, tot=cnt=0;
		rep(i,n) a[i]=gi;
		rep(i,n-1) a[i]=a[i+1]-a[i];
		C=mem, lab.clear(), root=null;
		bool flag0=1, flag1=1;
		T.init(n-1,a);
		
		for (int i=0;i<n-1;) {
			if (a[i]>0) {
				++i;
				continue;
			}
			int j;
			for (j=i+1;j<n-1;++j)
				if (a[j]>0)
					break;
			int l=i+1, r=j;
			if (r==n-1) ++r, flag1=0;
			if (l==1) --l, flag0=0;
			addSeg(l,r);
			i=j;
		}
		if (flag0) addSeg(0,0);
		if (flag1) addSeg(n,n);
		//visit(root);
		rep(k,q) {
			int style=gi;
			if (style==0) {
				int x=gi, y=gi;ll c=gi;
		//		if (Td==0 && k==29625) {
		//			flag=1;
		//		}
				if (x>1) Add(x-1,c);
		//		if (flag) return 0;
				if (y<n) Add(y,-c);
			}
			else {
				ll ans1,ans2;
				ans1=T.Sum();
				ans2=Ask(ans1);
				printf("%lld %lld\n", ans1, ans2);
			}
		//	if (Td==0 && k==29624) {
		//		printf("%d %d\n", tot, cnt);
		//	}
		}
	}
	
	return 0;
}
