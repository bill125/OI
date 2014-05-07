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

const int inf = ~0U>>1,maxn = 2000+10;
int n,m;
ll s1[maxn][maxn],s2[maxn][maxn];

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

inline ll gI() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	ll p = 0;
	do {
		p = p*10 + c-'0',c = getchar();
	} while (c >= '0' && c <= '9');
	return p;
}

template <class T> void debug(const T &a,const int &n) {rep(i,n) cout << a[i] << " ";puts("");}

int main() {
	setIO("test"); 
	
	n = gi,m = gi;
	fill(s1,0),fill(s2,0);
	For(i,1,n) For(j,1,n) s1[i][j] = s1[i-1][j] + gi;
	For(i,1,n) For(j,1,n) s2[i][j] = s2[i][j-1] + gi;
	
	rep(j,m) {
		int a = gi,b = gi,c = gi,d = gi;
		if (a > c) swap(a,c);--a;
		if (b > d) swap(b,d);--b;
		ll ans = 0;
		For(i,1,n) 
			ans += (s1[c][i] - s1[a][i]) * (s2[i][d] - s2[i][b]);
		printf("%lld\n", ans);
	}
	
	return 0;
}
