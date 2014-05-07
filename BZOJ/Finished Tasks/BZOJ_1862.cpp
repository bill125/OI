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

const int inf=~0U>>1, maxp=1000000+10;
int n;

struct Info {
	int x, time;
	Info(int _x,int _time) : x(_x), time(_time) {}
	Info() {}
	inline bool operator<(const Info & b) const { return x > b.x || x == b.x && time < b.time; }
	inline bool operator==(const Info & b) const { return x == b.x && time == b.time; }
};
map<string, Info> score;
struct Node {
	Info x;string Name;
	int sz;
	Node *s[2], *p;
	void sets(Node *t, int d) { t->p=this, s[d]=t; }
	int d() { return p->s[1]==this; }
	void upd();
	Node ();
}Tnull, *null=&Tnull, *root, mem[maxp], *C=mem;
Node::Node() { s[0]=s[1]=p=null;sz=0; }
Node* mk(Info x, string Name) {
	C->x=x, C->sz=1, C->Name=Name;
	return C++;
}
void Node::upd() { sz=s[0]->sz+s[1]->sz+1; }
void rot(Node *t) {
	Node *p=t->p;
	int d=t->d();
	p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (root==p) root=t;
	p->upd();
}
void splay(Node *t,Node *top=null) {
	while (t->p!=top) 
		if (t->p->p == top) rot(t);
		else {
			(t->p->d() == t->d()) ? rot(t->p) : rot(t);
			rot(t);
		}
	t->upd();
}
void Insert(Info k, string Name) {
	Node *c=mk(k, Name);
	if (root == null) { root=c; return ; }
	for (Node *t=root;;) {
		int d=t->x < k;
		if (t->s[d] == null) {
			t->sets(c, d);
			splay(t);
			return ;
		}
		else t=t->s[d];
	}
}
Node *select(int k) {
	for (Node *t=root;;) {
		int c=t->s[0]->sz+1;
		if (k==c) {splay(t); return t;}
		else if (k>c) k-=c, t=t->s[1];
		else t=t->s[0];
	}
}
Node *select(Info k) {
	for (Node *t=root;;) {
		if (t->x == k) {splay(t); return t;}
		else if (t->x < k) t=t->s[1];
		else t=t->s[0];
	}
}
Node *prev(Node *t) {
	splay(t);
	if (t->s[0]==null) return null;
	for (t=t->s[0];t->s[1]!=null;t=t->s[1]) ;
	if (t!=null) splay(t);
	return t;
}
Node *next(Node *t) {
	splay(t);
	if (t->s[1]==null) return null;
	for (t=t->s[1];t->s[0]!=null;t=t->s[0]) ;
	if (t!=null) splay(t);
	return t;
}
void Delete(Info k) {
	Node *t=select(k);
	Node *l=prev(t), *r=next(t);
	if (l==null && r==null) root=null;
	else if (l==null) {
		splay(r); r->sets(null, 0);
	}
	else if (r==null) {
		splay(l); l->sets(null, 1);
	}
	else {
		splay(l), splay(r,l);
		r->sets(null, 0);
	}
}

int main() {
	setIO("test");
	
	n=gi;
	root=null;
	rep(i,n) {
		char c[30];
		scanf("\n%s", c);
		string Name="";
		int l=strlen(c);
		if (!(c[1] >= '0' && c[1] <= '9')) For(j,1,l-1) Name=Name+c[j];
		
		if (c[0]=='?') {
			if (c[1] >= '0' && c[1] <= '9') {
				int k=0;
				For(j,1,l-1) k=k*10+c[j]-'0';
				Node *t=select(k);
				rep(i,10) {
					if (i) printf(" ");
					cout << t->Name;
					t=next(t);
					if (t==null) break;
				}
				puts("");
			}
			else {
				Info k=score[Name];
				Node *t=select(k);splay(t);
				printf("%d\n", t->s[0]->sz+1);
			}
		}
		else {
			int x=gi;
			if (score.count(Name)) Delete(score[Name]);
			score[Name]=Info(x, i);
			Insert(Info(x, i), Name);
		}
	}
	
	return 0;   
}
