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
#define ForS(i,a,b,step) for (int i = a;i != b;i += step)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define ForV(i,a) for (__typeof (a.begin()) i = a.begin();i != a.end();++i) 
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()

const int inf= ~0U>>1,maxn = 100000+10,maxT = 300000;
int n,m;
int num[maxn],pos[maxn];
ll a[maxn];

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

namespace Segment_Tree {
	int h,n;
	ll S[maxT],size[maxT];
	void init(int k) {
		n = k;
		for (h = 2;(1<<h) < n+2;++h) ;
		rep(i,(1<<h+1)) S[i] = size[i] = 0;
	}
	
	void refresh(int x) {
		S[x] = S[x<<1]+S[(x<<1)+1];
		size[x] = size[x<<1]+size[(x<<1)+1];
	}
	
	void Update(int x) {
		for (x>>=1;x;x>>=1) refresh(x);
	}
	
	void Change(int k,int x,int y) {
		k += (1<<h);
		S[k] = x;size[k] = y;
		Update(k);
	}
	
	ll Ask(int l,int r) {
		l += (1<<h)-1,r += (1<<h)+1;
		ll res = 0;
		while (l^r^1) {
			if (!(l&1)) res += S[l^1];
			if (r&1) res += S[r^1];
			l >>= 1,r >>= 1;
		}
		return res;
	}
	
	int Findkth(int k) {
		int x = 1;
		while (x < (1<<h)) {
			if (k > size[x<<1]) k -= size[x<<1],x = (x<<1)+1;
			else x <<= 1;
		}
		return x-(1<<h);
	}
}

namespace A = Segment_Tree;

bool cmp(int x,int y) {
	return a[x] < a[y];
}

int main() {
	setIO("test"); 
	
	scanf("%d %d", &n, &m);
	rep(i,n) a[i] = gi,num[i] = i;
	
	sort(num,num + n,cmp);
	rep(i,n) pos[num[i]] = i;
	
	A::init(n);
	
	ll all = 0,ans = (ll)inf*inf;
	rep(i,m) {
		A::Change(pos[i]+1,a[i],1);
		all += a[i];
	}

	For(i,m-1,n-1) {
		if (i != m-1) {
			all += a[i] - a[i-m];
			A::Change(pos[i-m]+1,0,0);
			A::Change(pos[i]+1,a[i],1);
		}
		//rep(j,n) printf("%d ", A::Ask(j+1,j+1));
		//puts("####"); 
		ll k,now,p,pos,t,S;
		pos = m/2;
		t = A::Findkth(pos);
		p = A::Ask(t,t);
		S = A::Ask(1,t);
		now = p*(m/2)-S + all-S-(m-m/2)*p;
		ans = min(ans,now);
		//printf("%lld %lld %lld\n", pos, S, now);
		
		pos = m/2+1;
		t = A::Findkth(pos);
		p = A::Ask(t,t);
		S = A::Ask(1,t);
		now = p*(m/2+1)-S + all-S-(m-m/2-1)*p;
		ans = min(ans,now);
	//	printf("%d %d %d\n", pos, S, now);
	}
	cout << ans << endl;
		
	return 0;
}
