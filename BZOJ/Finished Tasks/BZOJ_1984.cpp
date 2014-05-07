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
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define formap(i,e) for (map<int,int>::const_iterator i = e.begin();i != e.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()
#define v2(i) i->second
#define v1(i) i->first

const int inf = ~0U>>1,maxn = 100000+10,maxe = 200000+10,maxT = 1000000;
int n,tot = 0;
int h[maxn],son[maxn],dep[maxn],s[maxn],f[maxn],an[maxn];
int c[maxn],x[maxn],y[maxn];
bool v[maxn];
map<int,int> id[maxn];
struct Edge
{
	int to,next;
}E[maxe];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int gI()
{
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

void addedge(int a,int b)
{
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot;
}

void calc(int x)
{
	s[x] = 1;v[x] = true;
	ForE(i,x) if (!v[E[i].to]) {
		f[E[i].to] = x;dep[E[i].to] = dep[x] + 1;
		calc(E[i].to);
		s[x] += s[E[i].to];
	}
	if (x && (son[f[x]] == -1 || s[x] > s[son[f[x]]])) son[f[x]] = x;
}

void work(int x,int a)
{
	an[x] = a;
	if (son[x] != -1) id[x][son[x]] = id[son[x]][x] = ++tot,work(son[x],a);
	ForE(i,x) if (E[i].to != f[x] && E[i].to != son[x]) id[x][E[i].to] = id[E[i].to][x] = ++tot,work(E[i].to,E[i].to);
}

namespace sTree {
	int h;int T[maxT],Tag[maxT],Tag2[maxT];
	void init() {
		fill(T,0),fill(Tag,0);
		for (h = 2;(1<<h)<n+2;++h);
		rep(i,(1<<(h+1))) Tag2[i] = -1;
		rep(i,n) T[id[x[i]][y[i]]+(1<<h)] = c[i];
		repD(i,(1<<h)) T[i] = max(T[i<<1],T[(i<<1)+1]);
	}
	
	void Update(int x) {
		for (x>>=1;x;x>>=1) T[x] = max(T[x<<1],T[(x<<1)+1]);
	}
	
	void Pass_Down(int x) {
		if (Tag2[x]!=-1) {
			Tag2[x<<1]=Tag2[x],Tag2[(x<<1)+1]=Tag2[x];
			Tag[x<<1]=Tag[(x<<1)+1]=0;
			T[x<<1]=Tag2[x],T[(x<<1)+1]=Tag2[x];
			Tag2[x] = -1;
		}
		if (Tag[x]) {
			Tag[x<<1]+=Tag[x],Tag[(x<<1)+1]+=Tag[x];
			T[x<<1]+=Tag[x],T[(x<<1)+1]+=Tag[x];
			Tag[x] = 0;
		}
	}
	
	void Pass_to_Leaf(int x) {
		repD(i,h) Pass_Down(x>>(i+1));
	}
	
	void Change(int x,int a) {
		x += (1<<h);
		Pass_to_Leaf(x);
		T[x] = a;
		Update(x);
	}
	
	void Add(int x,int y,int w) {
		int l = x+(1<<h)-1,r = y+(1<<h)+1;
		Pass_to_Leaf(l),Pass_to_Leaf(r);
		while (l+1<r) {
			if (!(l&1)) Tag[l^1] += w,T[l^1] += w;
			if (r&1) Tag[r^1] += w,T[r^1] += w;
			l>>=1,r>>=1;
		}
		Update(x+(1<<h)-1),Update(y+(1<<h)+1);
	}
	
	void Cover(int x,int y,int w) {
		int l = x+(1<<h)-1,r = y+(1<<h)+1;
		Pass_to_Leaf(l),Pass_to_Leaf(r);
		while (l+1<r) {
			if (!(l&1)) Tag2[l^1] = w,Tag[l^1] = 0,T[l^1] = w;
			if (r&1) Tag2[r^1] = w,Tag[r^1] = 0,T[r^1] = w;
			l>>=1,r>>=1;
		}
		Update(x+(1<<h)-1),Update(y+(1<<h)+1);
	}
	
	int Ask(int x,int y) {
		int l = x+(1<<h)-1,r = y+(1<<h)+1,res = -1000000;
		Pass_to_Leaf(l),Pass_to_Leaf(r);
		while (l+1<r) {
			if (!(l&1)) res = max(res,T[l^1]);
			if (r&1) res = max(res,T[r^1]);
			l>>=1,r>>=1;
		}
		return res;
	}

}

void Cover(int x,int y,int w)
{
	while (an[x] != an[y]) {
		int tx = (an[x] == x) ? f[x] : an[x];
		int ty = (an[y] == y) ? f[y] : an[y];
		if (dep[tx] >= dep[ty] && x) { 
			if (an[x] == x) sTree::Change(id[tx][x],w);
			else sTree::Cover(id[tx][son[tx]],id[x][f[x]],w);
			x = tx;
		} 
		else {
			if (an[y] == y) sTree::Change(id[ty][y],w);
			else sTree::Cover(id[ty][son[ty]],id[y][f[y]],w);
			y = ty;
		}
	}
	if (x==y) return ;
	if (dep[x] > dep[y]) swap(x,y);
	sTree::Cover(id[x][son[x]],id[y][f[y]],w);
}

void Add(int x,int y,int w)
{
	
	while (an[x] != an[y]) {
		int tx = (an[x] == x) ? f[x] : an[x];
		int ty = (an[y] == y) ? f[y] : an[y];
		if (dep[tx] >= dep[ty] && x) { 
			if (an[x] == x) sTree::Add(id[tx][x],id[tx][x],w);
			else sTree::Add(id[tx][son[tx]],id[x][f[x]],w);
			x = tx;
		} 
		else {
			if (an[y] == y) sTree::Add(id[ty][y],id[ty][y],w);
			else sTree::Add(id[ty][son[ty]],id[y][f[y]],w);
			y = ty;
		}
	}
	if (x==y) return;
	if (dep[x] > dep[y]) swap(x,y);
	sTree::Add(id[x][son[x]],id[y][f[y]],w);
}

int Ask(int x,int y)
{
	int res = 0;
	while (an[x] != an[y]) {
		int tx = (an[x] == x) ? f[x] : an[x];
		int ty = (an[y] == y) ? f[y] : an[y];
		if (dep[tx] >= dep[ty] && x) { 
			if (an[x] == x) res = max(res,sTree::Ask(id[tx][x],id[tx][x]));
			else res = max(res,sTree::Ask(id[tx][son[tx]],id[x][f[x]]));
			x = tx;
		} 
		else {
			if (an[y] == y) res = max(res,sTree::Ask(id[ty][y],id[ty][y]));
			else res = max(res,sTree::Ask(id[ty][son[ty]],id[y][f[y]]));
			y = ty;
		}
	}
	if (x != y) {
		if (dep[x] > dep[y]) swap(x,y);
		res = max(res,sTree::Ask(id[x][son[x]],id[y][f[y]]));
	}
	return res;
}


int main()
{
	//setIO("test"); 
	
	scanf("%d", &n);
	rep(i,n) h[i] = son[i] = -1;
	rep(i,n-1) {
		x[i] = gi-1,y[i] = gi-1;c[i] = gi;
		addedge(x[i],y[i]),addedge(y[i],x[i]);
	}
	fill(v,0);tot = 0;dep[0] = 0;
	calc(0);work(0,0);
	sTree::init();
	char c[20];
	while (scanf("%s", c) && c[0] != 'S') {
		int a = gi,b = gi;
		if (c[1] == 'h') sTree::Change(id[x[a-1]][y[a-1]],b);
		else if (c[1] == 'o') Cover(a-1,b-1,gi);
		else if (c[0] == 'A') Add(a-1,b-1,gi);
		else printf("%d\n", Ask(a-1,b-1));
	}
	
	return 0;
}
