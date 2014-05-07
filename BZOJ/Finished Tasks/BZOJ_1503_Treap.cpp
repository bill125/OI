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

const int inf = ~0U>>1,maxn = 1000000+10;
int n,m,root,tot,delta,ans = 0;
int son[maxn][2],size[maxn],key[maxn],w[maxn],cnt[maxn];

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

void refresh(int x)
{
	size[x] = cnt[x] + size[son[x][0]] + size[son[x][1]];
}

//旋转 0为右旋 1为左旋
void rotate(int & x,int t)
{
	int y = son[x][t];
	son[x][t] = son[y][1-t],son[y][1-t] = x;
	refresh(x),refresh(y);
	x = y;
}

void init()
{
	tot = 1;key[1] = inf;root = 1;size[1] = 0;w[1] = inf;
}

void ins(int & x,int k)
{
	if (x) {
		if (key[x] == k) ++cnt[x];
		else {
			int t = k>key[x];
			ins(son[x][t],k);
			if (w[son[x][t]] < w[x]) rotate(x,t);
		}
	}
	else {
		x = ++tot;
		key[x] = k,cnt[x] = size[x] = 1;w[x] = rand()%inf;
		son[x][0] = son[x][1] = 0;
	}
	refresh(x);
}

bool leaf(int x)
{
	return !son[x][0] && !son[x][1];
}

void del(int & x,int k) 
{
	if (key[x] == k) {
		if (cnt[x] > 1) --cnt[x];
		else if (leaf(x)) {x = 0; return;}
		else {
			int t = w[son[x][0]] < w[son[x][1]];
			rotate(x,t);
			del(x,k);
		}
	}
	else del(son[x][key[x]<k],k);
	refresh(x);
}

int getKth(int x,int k)
{
	if (k <= size[son[x][0]]) return getKth(son[x][0],k);
	k -= size[son[x][0]] + cnt[x];
	if (k <= 0) return x;
	return getKth(son[x][1],k);
}

void Insert(int k)
{
	if (k < m) return ;
	ins(root,k-delta);++n;
}

int Ask(int k)
{
	if (k>n) return -1;
	return key[getKth(root,n+1-k)]+delta;
}

void Delete()
{	
	while (n) {
		int t = key[getKth(root,1)];
		if (t + delta >= m) return;
		del(root,t);
		--n,++ans;
	}
}

int main()
{
	//setIO("test"); 
	
	init();
	int _T;
	scanf("%d %d\n", &_T, &m);delta = 0;
	rep(i,_T) {
		char c = getchar();int k = gi;
		scanf("\n");
		if (c == 'I') Insert(k);
		else if (c == 'A' || c == 'S') {
			if (c == 'S') k = -k;
			delta += k;
			Delete();
		}
		else printf("%d\n", Ask(k));
	}
	printf("%d\n", ans);
		
	return 0;
}
