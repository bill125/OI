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

const int inf = ~0U>>1,maxn = 800000+10;
int n,m,ans1=inf;
struct Seg {
	int h,t;
}A[maxn];
struct state {
	int val;
	state(int _val):
		val(_val){}
	bool operator<(const state&o) const{return val>o.val;}
};
priority_queue<state> q1,q2;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

namespace bTree {
	int root,tot,size[maxn],son[maxn][2],cnt[maxn],key[maxn],w[maxn];
	
	void init() {
		root = tot = 1;
		cnt[1] = size[1] = son[1][0] = son[1][1] = 0;
		w[1] = key[1] = inf;
	}
	
	void refresh(int x) {
		size[x] = cnt[x] + size[son[x][0]] + size[son[x][1]];
	}
	
	void rotate(int & x,int t) {
		int y = son[x][t];
		son[x][t] = son[y][1-t],son[y][1-t] = x;
		refresh(x),refresh(y);
		x = y;
	}
	
	void ins(int & x,int k) {
		if (x) 
			if (key[x] == k) ++ cnt[x];
			else {
				int t = k>key[x];
				ins(son[x][t],k);
				if (w[x] > w[son[x][t]]) rotate(x,t);
			}
		else {
			x = ++tot;
			son[x][1] = son[x][0] = 0;
			cnt[x] = 1,key[x] = k,w[x] = rand();
		}
		refresh(x);
	}
	
	
	int getLower(int x,int k) {
		if (x==0||key[x]==k) return x;
		if (key[x]<k) {
			int t = getLower(son[x][1],k);
			if (t==0) return x;
		}
		else return getLower(son[x][0],k);
	}

	int getUpper(int x,int k) {
		if (x==0||key[x]==k) return x;
		if (key[x]<k) getUpper(son[x][1],k);
		else {
			int t = getUpper(son[x][0],k);
			if (t==0) return x;
		}
	}
	
	int Insert(int x) {
		int tU = getUpper(root,x),tL = getLower(root,x),res = inf;
		if (tU) res = min(res,abs(key[tU]-x));
		if (tL) res = min(res,abs(key[tL]-x)); 
		ins(root,x);
		
		return res;
	}
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

void Insert(int x,int k)
{
	ans1 = min(ans1,bTree::Insert(k));
	
	if (x != n-1) {
		q1.push(state(abs(k-A[x+1].h)));
		q2.push(state(abs(A[x].t-A[x+1].h)));
	}
	q1.push(state(abs(k-A[x].t)));
	
	while (q2.size() && q1.top().val == q2.top().val) q1.pop(),q2.pop();	
	A[x].t = k;
}

int main()
{
//	setIO("test"); 
	
	bTree::init();
	
	scanf("%d %d", &n, &m);
	rep(i,n) A[i].h = A[i].t = gi;
	
	rep(i,n) ans1 = min(ans1,bTree::Insert(A[i].h));
	rep(i,n-1) q1.push(state(abs(A[i].h-A[i+1].h)));
	
	rep(i,m) {
		char c[20];
		scanf("\n%s", c);
		if (c[0] == 'I') {
			int a,b;
			scanf("%d %d", &a, &b);
			Insert(a-1,b);
		}
		else if (c[4] == 'G') printf("%d\n", q1.top().val);
		else printf("%d\n", ans1);
	}
	
	return 0;
}
