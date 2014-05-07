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

const int inf = ~0U>>1,maxn = 30000+10,maxe = 60000+10,maxT = 1000000+10;
int n,m,tot;
int id[maxn],cnt[maxn],an[maxn],son[maxn],len[maxn],f[maxn],h[maxn],depth[maxn];
bool v[maxn];
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

int calc(int x) 
{
	cnt[x] = 1;v[x] = true;
	ForE(i,x) if (!v[E[i].to]) {
		f[E[i].to] = x;depth[E[i].to] = depth[x] + 1;
		cnt[x] += calc(E[i].to);
	}
	if (x && (son[f[x]] == -1 || cnt[x] > cnt[son[f[x]]])) son[f[x]] = x;
	return cnt[x];
}

void work(int x,int a)
{
	id[x] = tot++;an[x] = a;
	if (son[x] != -1) work(son[x],a);
	ForE(i,x) if (E[i].to != son[x] && E[i].to != f[x]) work(E[i].to,E[i].to);
} 

namespace sTree
{
	int h,T[maxT],T2[maxT];
	void init() {
		fill(T,0),fill(T2,0);
		for (h = 2;(1<<h)<n+2;++h);
		rep(i,n) T2[id[i]+(1<<h)+1] = T[id[i]+(1<<h)+1] = gi;
		repD(i,(1<<h)) {
			T[i] = T[i<<1]+T[(i<<1)+1];
			T2[i] = max(T2[i<<1],T2[(i<<1)+1]);
		}
	}
	
	int AskSum(int l,int r) {
		int res = 0;
		l += (1<<h)-1,r += (1<<h)+1;
		while (l^r^1) {
			if (!(l&1)) res += T[l+1];
			if (r&1) res += T[r-1];
			l>>=1,r>>=1;
		}
		return res;
	}
	
	int AskMax(int l,int r) {
		int res = -100000;
		l += (1<<h)-1,r += (1<<h)+1;
		while (l^r^1) {
			if (!(l&1)) res = max(res,T2[l+1]);
			if (r&1) res = max(res,T2[r-1]);
			l>>=1,r>>=1;
		}
		return res;
	}
	
	void Update(int x) {
		for (x>>=1;x;x>>=1) T[x]=T[x<<1]+T[(x<<1)+1],T2[x]=max(T2[x<<1],T2[(x<<1)+1]);
	}
	void Change(int x,int a) {
		T[x+(1<<h)+1] = T2[x+(1<<h)+1] = a;
		Update(x+(1<<h)+1);
	}
}

int AskMax(int a,int b)
{
	int res = -100000;
	while (an[a] != an[b]) {
		int ta = (an[a]==a) ? f[a] : an[a];
		int tb = (an[b]==b) ? f[b] : an[b];
		if (depth[ta] >= depth[tb] && a) {
			if (a == an[a]) res = max(res,sTree::AskMax(id[a]+1,id[a]+1));
			else res = max(res,sTree::AskMax(id[ta]+2,id[a]+1));
			a = ta;
		}
		else {
			if (b == an[b]) res = max(res,sTree::AskMax(id[b]+1,id[b]+1));
			else res = max(res,sTree::AskMax(id[tb]+2,id[b]+1));
			b = tb;
		}
	}
	if (depth[a]>depth[b]) swap(a,b);
	res = max(res,sTree::AskMax(id[a]+1,id[b]+1));
	return res;
}

int AskSum(int a,int b)
{
	int res = 0;
	while (an[a] != an[b]) {
		int ta = (an[a]==a) ? f[a] : an[a];
		int tb = (an[b]==b) ? f[b] : an[b];
		if (depth[ta] >= depth[tb] && a) {
			if (a == an[a]) res += sTree::AskSum(id[a]+1,id[a]+1);
			else res += sTree::AskSum(id[ta]+2,id[a]+1);
			a = ta;
		}
		else {
			if (b == an[b]) res += sTree::AskSum(id[b]+1,id[b]+1);
			else res += sTree::AskSum(id[tb]+2,id[b]+1);
			b = tb;
		}
	}
	if (depth[a]>depth[b]) swap(a,b);
	res += sTree::AskSum(id[a]+1,id[b]+1);
	return res;
}

int main()
{
	//setIO("test"); 
	
	scanf("%d", &n);
	rep(i,n) h[i] = son[i] = -1;
	rep(i,n-1) {
		int a,b;
		scanf("%d %d", &a, &b),--a,--b;
		addedge(a,b),addedge(b,a);
	}
	fill(cnt,0),fill(v,0);tot = 0;depth[0] = 0;
	calc(0);

	work(0,0);
	sTree::init();
	scanf("%d", &m);
	rep(i,m) {
		char c[20];int a,b;
		scanf("%s\n", c),a = gi-1,b = gi-1;
		if (c[1] == 'H') sTree::Change(id[a],b+1);
		else if (c[1] == 'M') printf("%d\n", AskMax(a,b));
		else printf("%d\n", AskSum(a,b));
	}
	puts("");
	
	return 0;
}
