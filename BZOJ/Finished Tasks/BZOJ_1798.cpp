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

const int inf = ~0U>>1,maxn = 100000+10,maxT = 700000+10;
int n,m;
int a[maxn];
ll P;

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

struct sTree {
	int n,h;
	ll a[maxT],T1[maxT],T2[maxT],size[maxT];

	void init(const int &_n,const int o[]) {
		n = _n;
		for (h = 1;(1 << h) < n+2; ++ h) ;
		rep(i,(1<<(h+1))) T1[i] = 1;
		fill(a,0),fill(T2,0),fill(size,0);
		rep(i,n) a[i+(1<<h)+1] = o[i],size[i+(1<<h)+1] = 1;
		repD(i,(1<<h)) refresh(i);
	}
	
	void refresh(const int&x) {
		a[x] = (a[x<<1] + a[(x<<1)+1]) % P;
		size[x] = size[x<<1] + size[(x<<1)+1];
	}
	
	void Pass_Down(const int&x) {
		#define y (x<<1)
		#define z (x<<1)+1
		if (T1[x] != 1) {
			a[y] = (a[y] * T1[x]) % P;
			T1[y] = (T1[y] * T1[x]) % P;
			T2[y] = (T2[y] * T1[x]) % P;
			a[z] = (a[z] * T1[x]) % P;
			T1[z] = (T1[z] * T1[x]) % P;
			T2[z] = (T2[z] * T1[x]) % P;
			T1[x] = 1;
		}
		if (T2[x]) {
			a[y] = (a[y] + T2[x]*size[y]) % P;
			T2[y] = (T2[y] + T2[x]) % P;
			a[z] = (a[z] + T2[x]*size[z]) % P;
			T2[z] = (T2[z] + T2[x]) % P;
			T2[x] = 0;
		}
		#undef y
		#undef z
	}
	
	void Pass_to_Leaf(int x) {
		repD(i,h-1) Pass_Down(x >> (i+1));
	}
	
	void Update(int x) {
		for (x >>= 1;x;x >>= 1) refresh(x);
	}
	
	ll Ask(int l,int r) {
		ll res = 0;
		l += (1<<h) - 1,r += (1<<h) + 1;
		Pass_to_Leaf(l),Pass_to_Leaf(r); 
		while (l + 1 < r) {
			if (!(l&1)) res = (res + a[l^1]) % P;
			if (r&1) res = (res + a[r^1]) % P;
			l >>= 1,r >>= 1;
		}
		return res;
	}
	
	void Add(int x,int y,ll c) {
		int l = x + (1<<h) - 1,r = y + (1<<h) + 1;
		Pass_to_Leaf(l),Pass_to_Leaf(r);
		while (l + 1 < r) {
			if (!(l&1)) a[l^1] = (a[l^1] + (c*size[l^1]) ) % P,T2[l^1] = (T2[l^1] + c) % P;
			if (r&1) a[r^1] = (a[r^1] + c*size[r^1]) % P,T2[r^1] = (T2[r^1] + c) % P;
			l >>= 1,r >>= 1;
		}
		l = x + (1<<h) - 1,r = y + (1<<h) + 1;
		Update(l),Update(r);
	}
	
	void Multi(int x,int y,ll c) {
		int l = x + (1<<h) - 1,r = y + (1<<h) + 1;
		Pass_to_Leaf(l),Pass_to_Leaf(r);
		while (l + 1 < r) {
			if (!(l&1)) a[l^1] = (a[l^1] * c) % P,T1[l^1] = (T1[l^1] * c) % P,T2[l^1] = (T2[l^1] * c) % P;
			if (r&1) a[r^1] = (a[r^1] * c) % P,T1[r^1] = (T1[r^1] * c) % P,T2[r^1] = (T2[r^1] * c) % P;
			l >>= 1,r >>= 1;
		}
		l = x + (1<<h) - 1,r = y + (1<<h) + 1;
		Update(l),Update(r);
	}
}T;

int main() {
	setIO("test"); 
	
	n = gi,P = gi;
	rep(i,n) a[i] = gi;
	T.init(n,a);
	
	m = gi;
	while (m--) {
		int style = gi;
		if (style == 1) {
			int l = gi,r = gi,c = gi;
			T.Multi(l,r,c);
		}
		else if (style == 2) {
			int l = gi,r = gi,c = gi;
			T.Add(l,r,c);
		}
		else {
			int l = gi,r = gi;
			printf("%lld\n", T.Ask(l,r));
		}
	}
	
	return 0;
}
