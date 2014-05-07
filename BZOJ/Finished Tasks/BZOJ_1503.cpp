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
using std::make_pair;
 
typedef long long ll;
typedef double db;
typedef std::pair <int, int> Pair;
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

const int inf = ~0U>>1;
int n = 0,m,Td,delta = 0,ans = 0;

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

namespace Treap {
	const int maxT = 300000+10;
	int root,tot;
	int son[maxT][2],size[maxT],key[maxT],w[maxT];
	void init() {
		root = tot = 1;
		w[1] = key[1] = inf;
		size[1] = 0;
	}
	void refresh(int x) {
		size[x] = 1 + size[son[x][0]] + size[son[x][1]];
	}
	int merge(int a,int b) {
		if (!a) return b;
		if (!b) return a;
		if (key[a] < key[b]) {
			son[a][1] = merge(son[a][1],b);
			refresh(a);
			return a;
		}
		else {
			son[b][0] = merge(a,son[b][0]);
			refresh(b);
			return b;
		}
	}
	Pair split(int a,int n) {
		if (!a) return make_pair(0,0);
		if (n <= size[son[a][0]]) {
			Pair res = split(son[a][0],n);
			son[a][0] = 0;
			refresh(a);
			return make_pair(res.first,merge(res.second,a));
		}
		else {
			Pair res = split(son[a][1],n - 1 - size[son[a][0]]);
			son[a][1] = 0;
			refresh(a);
			return make_pair(merge(a,res.first), res.second);
		} 
	}
	void AddNode(int k) {
		++tot;
		son[tot][0] = son[tot][1] = 0;
		key[tot] = k,w[tot] = rand();
		size[tot] = 1;
	}
	int getpos(int x,int k) {
		if (!x) return 0;
		if (k == key[x]) return 1;
		if (k < key[x]) return getpos(son[x][0],k);
		return size[son[x][0]]+1+getpos(son[x][1],k);
	}
	void ins(int k) {
		int n = getpos(root,k);
		Pair t = split(root,n);
		AddNode(k);
		root = merge(merge(t.first,tot),t.second);
	}
	int getkth(int x,int k) {
		if (k <= size[son[x][0]]) return getkth(son[x][0],k);
		k -= size[son[x][0]] + 1;
		if (k <= 0) return x;
		else return getkth(son[x][1],k);
	}
	int Ask(int k) {
		return key[getkth(root,n-k+1)];
	}
	int top() {
		return key[getkth(root,1)];
	}
	void pop() {
		Pair t = split(root,1);
		root = t.second;
	}
	void debug(int x) {
		if (!x) return;
		debug(son[x][0]);
		printf("%d\n",key[x]);
		debug(son[x][1]);
	}
}

void Insert(int k) 
{
	if (k<m) return ;
	Treap::ins(k-delta);
	++n;
}

void Add(int k)
{
	delta += k;
	if (k >= 0) return;
	while (n && Treap::top()+delta<m) Treap::pop(),--n,++ans;
}

int Ask(int k)
{
	if (k > n) return -1;
	return Treap::Ask(k)+delta;
}

int main()
{
	setIO("test"); 
	
	Treap::init();
	scanf("%d %d\n", &Td, &m);
	rep(i,Td) {
		char c = getchar();int k = gi;
		scanf("\n");
		switch (c) { 
			case 'I' : Insert(k);break;
			case 'S' : Add(-k);break;
			case 'A' : Add(k);break;
			case 'F' : printf("%d\n", Ask(k));break;
		}
		//Treap::debug(Treap::root);
		//printf("#####################\n");
		//if (i == 3) return 0;
	}
	printf("%d\n", ans);
		
	return 0;
}
