#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (vector<Edge>::iterator i = E[a].begin();i != E[a].end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define pf push_front
#define gi gI()

const int inf = ~0U>>1,maxn = 50000+10;
int n,m;

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

ll gI() {
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	ll p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

template <class T> void debug(const T &a,const int &n) {rep(i,n) cout << a[i] << " ";puts("");}

struct Node {
	Node *s[2],*p;
	int sz;
	ll mx,v,add;
	bool rev;
	Node () {
		sz = 0;
		mx = v = -inf;
		add = 0;
	}
	void relax();
	void upd() {
		sz = s[0]->sz + s[1]->sz + 1;
		mx = max(v,max(s[0]->mx,s[1]->mx));
	}
	int d() {
		return p->s[1] == this;
	}
	void sets(Node *t,int d) {
		s[d] = t;
		t->p = this;
	}
	void addIt(ll t) {
		mx += t,v += t,add += t;
	}
	void revIt() {
		rev ^= 1;
	}
}Tnull, *null = &Tnull;
Node *root,mem[maxn],*C = mem;

void Node::relax() {
	if (add != 0) {
		rep(i,2) if (s[i] != null) s[i]->addIt(add);
		add = 0;
	}
	if (rev) {
		swap(s[0],s[1]);
		rep(i,2) if (s[i] != null) s[i]->revIt();
		rev = 0;
	}
}

void rotate(Node *t) {
	Node *p = t->p;
	p->relax();
	t->relax();
	int d = t->d();
	p->p->sets(t,p->d());
	p->sets(t->s[!d],d);
	t->sets(p,!d);
	p->upd();
	if (root == p) root = t;
}

void splay(Node *t,Node *top = null) {
	while (t->p != top) 
		if (t->p->p == top) 
			rotate(t);
		else 
			(t->p->d() == t->d()) ? (rotate(t->p),rotate(t)) : (rotate(t),rotate(t));
	t->upd();
}

Node* mk(int x) {
	C->v = C->mx = x;
	C->sz = 1;
	C->s[0] = C->s[1] = null;
	C->add = C->rev = 0;
	return C++;
}

Node* build(int l,int r) {
	if (l >= r) return null;
	int m = (l + r) >> 1;
	Node *t = mk(0);
	t->sets(build(l,m),0);
	t->sets(build(m+1,r),1);
	t->upd();
	return t;
}

Node* select(int k) {
	for (Node* t = root;;) {
		t->relax();
		int c = t->s[0]->sz + 1;
		if (c == k)
			return t;
		else 
			if (k > c) 
				k -= c,t = t->s[1];
			else 
				t = t->s[0];
	}
}

Node*&get(int l,int r) {
	Node*L = select(l);
	Node*R = select(r+1);
	
	splay(L);
	splay(R,L);
	return R->s[0]; 
}

int main() {
	setIO("test"); 
	
	n = gi,m = gi;
	root = build(0,n+2);
	root->p = null;

	while (m--) {
		int style = gi,l = gi,r = gi;
		Node*&t = get(l,r+1);
		if (style == 1) {
			t->addIt(gi);
			splay(t);
		}
		else if (style == 2) {
			t->revIt();
			splay(t);
		}
		else {
			printf("%lld\n", t->mx);
		}
	}
	
	return 0;
}
