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
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define ForV(i,a) for (__typeof (a.begin()) i = a.begin();i != a.end();++i) 
#define fill(a,b) memset(a,b,sizeof(a))
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define gi gI()
#define P 1000000000000000000

const int inf = ~0U>>1,maxn = 100000+10;
ll n,L,p;
ll dp[maxn],s[maxn],t[maxn];
int Stack[maxn];
ll MAX[11] = {0,1000000000000000000,1000000000,1000000,31622,3981,1000,372,177,100,63};
char c[50];

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

void debug(int *a,int n) {rep(i,n) printf("%d ", a[i]);puts("");}
void debug(ll *a,int n) {rep(i,n) cout << a[i] << " ";puts("");}

ll fast_pow(ll a,ll b) {
	ll res = 1,t = a;
	while (b) {
		if (b&1) res *= t;
		b >>= 1;
		if (b) t *= t;
	}
	return res;
}

ll get(ll x,int y) {
	if (abs(x-L-1-t[y]) > MAX[p]) return P+1;
	ll res = dp[y] + fast_pow(abs(x-L-1-t[y]),p);
	return (res > P) ? P+1 : res;
}

ll rev(int x,int y,ll left) {
	ll l = left,r = 100000000;
	while (l + 1 < r) {
		ll m = (l + r) >> 1;
		ll a = get(m,y),b = get(m,x);
		//x > y
		if (a > P) {
			if (b > P) {
				if (m < L+1+t[y]) 
					l = m;
				else 
					r = m;
			}
			else {
				r = m;
			}
		}
		else {
			if (b > P) {
				l = m;
			}
			else {
				if (a > b)
					r = m;
				else 
					l = m;
			}
		}
	}
	return l;
}

int main() {
	setIO("test"); 
	
	int Td = gi;
	while (Td--) {
		n = gi,L = gi,p = gi;
		s[0] = 0;
		rep(i,n) {
			scanf("\n%s", c);
			s[i+1] = s[i] + strlen(c);
		}      
		if (p == 0) {
			puts("1");
			puts("--------------------");
			continue;
		}
		For(i,0,n)
			t[i] = s[i] + i;  
		dp[0] = 0;
		int l = 0,r = 1;
		Stack[0] = 0;
		For(i,1,n) {
			while (l + 1 < r && rev(Stack[l+1],Stack[l],t[Stack[l]]) < t[i]) ++ l;
			dp[i] = get(t[i],Stack[l]);
			while (l + 1 < r && rev(i,Stack[r-1],t[i]) <= rev(Stack[r-1],Stack[r-2],t[i])) -- r;
			Stack[r++] = i;
		}
		if (dp[n] > P) {
			puts("Too hard to arrange");
			puts("--------------------");
		}
		else {
			cout << dp[n] << endl;
			puts("--------------------");
		}
	}
	
	return 0;
}
