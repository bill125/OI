#include <cstdio>
#include <cstdlib>
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
#define ForS(i,a,b,step) for (int i = a;i != b;i += step)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define ForV(i,a) for (__typeof(a.begin()) i = a.begin();i != a.end();++i) 
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()

const int inf = ~0U>>1,maxe = 200000+10,maxn = 100000+10,P = 314000000;
int n,m;
int aMin[maxn],aMax[maxn],num[maxn];
struct Rule {
	vector<int> item;
	int From,Diamonds,Size;
}R[maxn];

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

int gI() {
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

namespace A{
	int tot = -1;
	int h[maxn],q[maxn],f[maxn];
	struct Edge {
		int next,r;
	}E[maxe];
	Rule _R[maxn];
}

namespace Heap {
	int _n = 0;
	int q[maxn];
		
	void Down(int x) {
		int a;
		for (;(x<<1)<=_n;x = a) {
			a = ((x<<1)<_n && A::_R[q[(x<<1)+1]].Diamonds<A::_R[q[x<<1]].Diamonds) ? (x<<1)+1 : (x<<1);
			if (A::_R[q[x]].Diamonds < A::_R[q[a]].Diamonds) return;
			swap(num[q[a]],num[q[x]]);
			swap(q[a],q[x]);
		}
	}
	
	void Up(int x) {
		for (;x>1 && A::_R[q[x]].Diamonds < A::_R[q[x>>1]].Diamonds;x>>=1) {
			swap(num[q[x]],num[q[x>>1]]);
			swap(q[x],q[x>>1]);
		}
	}
	
	void Add(int x) {
		q[++_n] = x,num[x] = _n;
		Up(_n);
	}
	
	int Top() {
		if (_n < 1) return -1;
		return q[1];
	}
	
	int Pop() {
		if (_n < 1) return -1;
		swap(num[q[1]],num[q[_n]]);
		swap(q[1],q[_n]);
		--_n,Down(1);
		return q[_n+1];
	}
}

namespace A {	
	void init() {
		rep(i,n) h[i] = -1;
		rep(i,m) _R[i].From = R[i].From,_R[i].Diamonds = R[i].Diamonds,_R[i].Size = R[i].Size;
		rep(i,n) f[i] = -1;
	}
	
	void Add_Edge(int x,int y) {
		++tot;
		E[tot].r = y,E[tot].next = h[x],h[x] = tot;
	}
	
	void Build() {
		rep(i,m) {
			rep(j,R[i].Size) 
				Add_Edge(R[i].item[j],i);
		}
	}
	
	void Find() {
		rep(i,m) 
			if (!_R[i].Size) 
				Heap::Add(i);
		rep(i,n) {
			int x;
			for (x = Heap::Pop();x != -1 && f[_R[x].From] != -1;x = Heap::Pop()) ;
			if (x == -1) break;
			f[_R[x].From] = _R[x].Diamonds;
			ForE(j,_R[x].From) {
				int t = E[j].r;
				_R[t].Diamonds = min(f[_R[x].From]+_R[t].Diamonds,P);
				if (!--_R[t].Size) Heap::Add(t);
			}
		}
		rep(i,n) {
			aMin[i] = f[i];
			if (f[i] == -1) aMax[i] = -1;
		}
	}
	
	void Run() {
		init();
		Build();
		Find();
	}
}

namespace B{
	int tot = -1;
	int h[maxn],q[maxn],f[maxn];
	struct Edge {
		int next,r;
	}E[maxe];
	Rule _R[maxn];
	
	void init() {
		rep(i,n) {
			f[i] = inf,h[i] = -1;
			if (aMax[i] == -1) f[i] = -1;
		}
	}
	
	void Add_Edge(int x,int y) {
		++tot;
		E[tot].r = y,E[tot].next = h[x],h[x] = tot;
	}
	
	void Build() {
		rep(i,m) 
			Add_Edge(R[i].From,i);
	}
	
	void Work(int x) {
		f[x] = -2;
		int res = -2;
		ForE(i,x) {
			int t = E[i].r,now = R[t].Diamonds;
			bool flag = true;
			rep(j,R[t].Size) {
				int k = R[t].item[j];
				if (f[k] == -1) {flag = false;break;}
				if (f[k] == inf) Work(k);
				if (f[k] == -2 || now == -2) now = -2;
				else now += f[R[t].item[j]]; 
				now = min(now,P);
			}
			if (!flag) continue;
			if (now == -2) res = -2;
			else res = max(now,res);
			if (res == -2) break;
		}
		f[x] = res;
	}
	
	void Run() {
		init();
		Build();
		rep(i,n) 
			if (f[i] == inf)
				Work(i);
		rep(i,n) aMax[i] = f[i];
	}
}


int main() {
	setIO("test"); 
	
	scanf("%d %d", &m, &n);
	rep(i,m) {
		R[i].From = gi-1;R[i].Diamonds = R[i].Size = 0;
		int k = gi; 
		while (k--) {
			int a = gi;
			if (a == -1) ++R[i].Diamonds;
			else R[i].item.pb(a-1),++R[i].Size; 
		}
	}
	
	A::Run();
	B::Run();
	
	rep(i,n) printf("%d %d\n", aMin[i], aMax[i]);
		
	return 0;
}
