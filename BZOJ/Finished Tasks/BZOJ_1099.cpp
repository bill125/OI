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

const int maxn = 50000+10,maxl = 200000+10,maxT = 150000+10;
const ll inf = ~0U>>1;
int n,_n[9];
ll a[maxn],b[maxn],c[maxn],x[maxn],key[9][maxl];
int style[9][maxl],l[9][maxl],r[9][maxl],num[9][maxl],NUM[maxn],NUM2[maxn];
int x2[maxn],x3[maxn];
ll add[9][maxl],ans[maxn];
bool v[9][maxl];
map<int,int> L1,R1,L2,R2;

void setIO(string name)
{
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
	#endif
}

namespace sTree {
	ll T[9][maxT];
	int h;
	void init() {
		for (h = 2;(1<<h) < n+2;++h);
		rep(i,9) rep(j,1<<h+1) T[i][j] = inf*inf/4;
	}
	void Update(int k,int x) {
		for (x>>=1;x;x>>=1) T[k][x] = min(T[k][x<<1],T[k][(x<<1)+1]);
	}
	void Change(int k,int x,ll p) {
		x += (1<<h);
		T[k][x] = p;
		Update(k,x);
	}
	ll Ask(int k,int l,int r) {
		l += (1<<h)-1,r += (1<<h)+1;
		ll res = inf*inf;
		while (l+1<r) {
			if (!(l&1)) res = min(res,T[k][l^1]);
			if (r&1) res = min(res,T[k][r^1]);
			l >>= 1,r >>= 1;
		}
		return res;
	}
	ll get(int k,int x) {
		return T[k][x+(1<<h)];
	}
}

bool cmp(int a,int b) {
	return x[a] > x[b];
}

bool cmp2(int a,int b) {
	return x[a] < x[b];
}

void getnum() {
	int t = 0;
	rep(i,n) x2[i] = x3[i] = i;
	sort(x2,x2 + n,cmp);
	rep(i,n) NUM[x2[i]] = ++t;
	rep(i,n) {
		if (!L1.count(x[i])) L1[x[i]] = NUM[i];
		else L1[x[i]] = min(L1[x[i]],NUM[i]);
		if (!R1.count(x[i])) R1[x[i]] = NUM[i];
		else R1[x[i]] = max(R1[x[i]],NUM[i]);
	}
	sort(x3,x3 + n,cmp2);
	t = 0;
	rep(i,n) NUM2[x3[i]] = ++t;
	rep(i,n) {
		if (!L2.count(x[i])) L2[x[i]] = NUM2[i];
		else L2[x[i]] = min(L2[x[i]],NUM2[i]);
		if (!R2.count(x[i])) R2[x[i]] = NUM2[i];
		else R2[x[i]] = max(R2[x[i]],NUM2[i]);
	}
}


void qSort(int k,int l,int r) {
	int t = num[k][(l+r)>>1],x = key[k][t],y = style[k][t];
	int i = l,j = r;
	while (i<j) {
		while (key[k][num[k][i]] > x || key[k][num[k][i]] == x && style[k][num[k][i]] < y) ++i;
		while (key[k][num[k][j]] < x || key[k][num[k][j]] == x && style[k][num[k][j]] > y) --j;
		if (i <= j) swap(num[k][i++],num[k][j--]);
	}
	if (i < r) qSort(k,i,r);
	if (l < j) qSort(k,l,j);
}

void qSort2(int k,int l,int r) {
	int t = num[k][(l+r)>>1],x = key[k][t],y = style[k][t];
	int i = l,j = r;
	while (i<j) {
		while (key[k][num[k][i]] < x || key[k][num[k][i]] == x && style[k][num[k][i]] < y) ++i;
		while (key[k][num[k][j]] > x || key[k][num[k][j]] == x && style[k][num[k][j]] > y) --j;
		if (i <= j) swap(num[k][i++],num[k][j--]);
	}
	if (i < r) qSort2(k,i,r);
	if (l < j) qSort2(k,l,j);
}

void special() {
	c[0] = abs(x[1]-x[0]),c[n-1] = abs(x[n-1]-x[n-2]);
	//0与1
	ans[0] = min(ans[0],ans[n]-abs(x[2]-x[1])+abs(x[2]-x[0]));
	ans[1] = min(ans[1],ans[n]-abs(x[2]-x[1])+abs(x[2]-x[0]));
	//n-2与n-1
	ans[n-1] = min(ans[n-1],ans[n]-abs(x[n-3]-x[n-2])+abs(x[n-3]-x[n-1]));
	ans[n-2] = min(ans[n-2],ans[n]-abs(x[n-3]-x[n-2])+abs(x[n-3]-x[n-1]));
	//0与1<i<n-1
	For(i,2,n-2) {
		ans[0] = min(ans[0],ans[n]-c[i]-c[0]+abs(x[i]-x[1])+abs(a[i]-x[0])+abs(b[i]-x[0]));
		ans[i] = min(ans[i],ans[n]-c[i]-c[0]+abs(x[i]-x[1])+abs(a[i]-x[0])+abs(b[i]-x[0]));
	}
	//n-1与0<i<n-2
	For(i,1,n-3) {
		ans[n-1] = min(ans[n-1],ans[n]-c[i]-c[n-1]+abs(a[i]-x[n-1])+abs(b[i]-x[n-1])+abs(x[n-2]-x[i]));
		ans[i] = min(ans[i],ans[n]-c[i]-c[n-1]+abs(a[i]-x[n-1])+abs(b[i]-x[n-1])+abs(x[n-2]-x[i]));
	}
	//0与n-1
	ans[0] = min(ans[0],ans[n]-c[0]-c[n-1]+abs(x[1]-x[n-1])+abs(x[n-2]-x[0]));
	ans[n-1] = min(ans[n-1],ans[n]-c[0]-c[n-1]+abs(x[1]-x[n-1])+abs(x[n-2]-x[0]));
	//i与i+1 0<i<n-2
	For(i,1,n-3) {
		ans[i] = min(ans[i],ans[n]-abs(x[i-1]-x[i])-abs(x[i+1]-x[i+2])+abs(x[i-1]-x[i+1])+abs(x[i]-x[i+2]));
		ans[i+1] = min(ans[i+1],ans[n]-abs(x[i-1]-x[i])-abs(x[i+1]-x[i+2])+abs(x[i-1]-x[i+1])+abs(x[i]-x[i+2]));
	}
}

void print();

void work() {
	ll t,maxH = 0,minH = inf;
	fill(_n,0);
	rep(i,n) maxH = max(maxH,x[i]),minH = min(minH,x[i]);
	//printf("%lld %lld\n", maxH,minH);
	
	//1 xi<=aj xj<=ai
	rep(i,n) style[0][t = _n[0]++] = 1,key[0][t] = x[i],add[0][t] = +a[i]+b[i]-c[i]-2*x[i],l[0][t] = minH,r[0][t] = a[i];
	rep(i,n) style[0][t = _n[0]++] = 0,key[0][t] = a[i],add[0][t] = +a[i]+b[i]-c[i]-2*x[i],l[0][t] = NUM[i];
	
	//2 xi<=aj ai<=xj<-bi
	rep(i,n) style[1][t = _n[1]++] = 1,key[1][t] = x[i],add[1][t] = -a[i]+b[i]-c[i]-2*x[i],l[1][t] = a[i],r[1][t] = b[i];
	rep(i,n) style[1][t = _n[1]++] = 0,key[1][t] = a[i],add[1][t] = +a[i]+b[i]-c[i]		  ,l[1][t] = NUM[i]; 
	
	//3 xi<=aj bi<=xj
	rep(i,n) style[2][t = _n[2]++] = 1,key[2][t] = x[i],add[2][t] = -a[i]-b[i]-c[i]-2*x[i],l[2][t] = b[i],r[2][t] = maxH;
	rep(i,n) style[2][t = _n[2]++] = 0,key[2][t] = a[i],add[2][t] = +a[i]+b[i]-c[i]+2*x[i],l[2][t] = NUM[i];
	
	//4 aj<=xi<=bj xj<=ai
	rep(i,n) style[3][t = _n[3]++] = 1,key[3][t] = x[i],add[3][t] = +a[i]+b[i]-c[i]		  ,l[3][t] = minH,r[3][t] = a[i];
	rep(i,n) style[3][t = _n[3]++] = 0,key[3][t] = b[i],add[3][t] = -a[i]+b[i]-c[i]-2*x[i],l[3][t] = NUM[i];
	rep(i,n) style[3][t = _n[3]++] = 2,key[3][t] = a[i],add[3][t] = inf*inf/4			  ,l[3][t] = NUM[i];
	
	//5 aj<=xi<=bj ai<=xj<=bi
	rep(i,n) style[4][t = _n[4]++] = 1,key[4][t] = x[i],add[4][t] = -a[i]+b[i]-c[i],l[4][t] = a[i],r[4][t] = b[i];
	rep(i,n) style[4][t = _n[4]++] = 0,key[4][t] = b[i],add[4][t] = -a[i]+b[i]-c[i],l[4][t] = NUM[i];
	rep(i,n) style[4][t = _n[4]++] = 2,key[4][t] = a[i],add[4][t] = inf*inf/4	   ,l[4][t] = NUM[i];
	 
	//6 aj<=xi<=bj bi<=xj
	rep(i,n) style[5][t = _n[5]++] = 1,key[5][t] = x[i],add[5][t] = -a[i]-b[i]-c[i]		  ,l[5][t] = b[i],r[5][t] = maxH;
	rep(i,n) style[5][t = _n[5]++] = 0,key[5][t] = b[i],add[5][t] = -a[i]+b[i]-c[i]+2*x[i],l[5][t] = NUM[i];
	rep(i,n) style[5][t = _n[5]++] = 2,key[5][t] = a[i],add[5][t] = inf*inf/4			  ,l[5][t] = NUM[i];
	
	//7 bj<=xi xj<=ai
	rep(i,n) style[6][t = _n[6]++] = 1,key[6][t] = x[i],add[6][t] = +a[i]+b[i]-c[i]+2*x[i],l[6][t] = minH,r[6][t] = a[i];
	rep(i,n) style[6][t = _n[6]++] = 0,key[6][t] = b[i],add[6][t] = -a[i]-b[i]-c[i]-2*x[i],l[6][t] = NUM2[i];
	
	//8 bj<=xi ai<=xj<=bi
	rep(i,n) style[7][t = _n[7]++] = 1,key[7][t] = x[i],add[7][t] = -a[i]+b[i]-c[i]+2*x[i],l[7][t] = a[i],r[7][t] = b[i];
	rep(i,n) style[7][t = _n[7]++] = 0,key[7][t] = b[i],add[7][t] = -a[i]-b[i]-c[i]		  ,l[7][t] = NUM2[i];
	
	//9 bj<=xi bi<=xj
	rep(i,n) style[8][t = _n[8]++] = 1,key[8][t] = x[i],add[8][t] = -a[i]-b[i]-c[i]+2*x[i],l[8][t] = b[i],r[8][t] = maxH;
	rep(i,n) style[8][t = _n[8]++] = 0,key[8][t] = b[i],add[8][t] = -a[i]-b[i]-c[i]+2*x[i],l[8][t] = NUM2[i];
	
	rep(i,9) rep(j,_n[i]) num[i][j] = j;
	rep(i,6) qSort(i,0,_n[i]-1);
	For(i,6,8) qSort2(i,0,_n[i]-1);
	
	sTree::init();
	
	fill(v,0);
	ll t1,t2;
	rep(i,6) {
		rep(p,_n[i]) {
			int j = num[i][p];
			if (j%n==0||j%n==n-1) continue;
			switch (style[i][j]) {
				case 1 :
					if (v[i][j%n-1]) t1 = sTree::get(i,NUM[j%n-1]),sTree::Change(i,NUM[j%n-1],inf*inf/4);
					if (v[i][j%n+1]) t2 = sTree::get(i,NUM[j%n+1]),sTree::Change(i,NUM[j%n+1],inf*inf/4);
					ans[j%n] = min(ans[j%n],ans[n]+add[i][j]+sTree::Ask(i,L1[r[i][j]],R1[l[i][j]])); 
					if (v[i][j%n-1]) sTree::Change(i,NUM[j%n-1],t1);
					if (v[i][j%n+1]) sTree::Change(i,NUM[j%n+1],t2);
					break;
				case 0 : sTree::Change(i,l[i][j],add[i][j]);v[i][j%n] = 1;break;
				case 2 : sTree::Change(i,l[i][j],add[i][j]);v[i][j%n] = 0;break;
			}
		}
	}
	For(i,6,8) {
		rep(p,_n[i]) {
			int j = num[i][p];
			if (j%n==0||j%n==n-1) continue;
			switch (style[i][j]) {
				case 1 :
					if (v[i][j%n-1]) t1 = sTree::get(i,NUM2[j%n-1]),sTree::Change(i,NUM2[j%n-1],inf*inf/4);
					if (v[i][j%n+1]) t2 = sTree::get(i,NUM2[j%n+1]),sTree::Change(i,NUM2[j%n+1],inf*inf/4);
					ans[j%n] = min(ans[j%n],ans[n]+add[i][j]+sTree::Ask(i,L2[l[i][j]],R2[r[i][j]]));
					if (v[i][j%n-1]) sTree::Change(i,NUM2[j%n-1],t1);
					if (v[i][j%n+1]) sTree::Change(i,NUM2[j%n+1],t2);
					break; 
				case 0 : sTree::Change(i,l[i][j],add[i][j]);v[i][j%n] = 1;break;
				case 2 : sTree::Change(i,l[i][j],add[i][j]);v[i][j%n] = 0;break;
			}
		}
	}
}

void print() {
	rep(i,n) printf("%lld\n", ans[i]);
}

ll gI()
{
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	ll p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

int main()
{
	setIO("test"); 
	
	scanf("%d", &n);
	rep(i,n) x[i] = gi;
	rep(i,n) if (i != 0 && i != n-1) a[i] = min(x[i+1],x[i-1]),b[i] = max(x[i+1],x[i-1]),c[i] = abs(a[i]-x[i])+abs(b[i]-x[i]);
	rep(i,n-1) ans[n] += abs(x[i]-x[i+1]);
	rep(i,n) ans[i] = ans[n];
	a[0] = b[0] = x[1],a[n-1] = b[n-1] = x[n-2];
	
	if (n == 2) {
		printf("%lld\n%lld\n", ans[2], ans[2]);
		return 0;
	}
	special();
	getnum();
	work();
	print();
	
	return 0;
}
