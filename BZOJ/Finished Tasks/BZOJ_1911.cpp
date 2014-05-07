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

const int inf = ~0U>>1,maxn = 1000000+10;
ll n,a,b,c;
ll dp[maxn];
int S[maxn],Q[maxn];

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

ll T(int j,int k) {
	return (ll)((db)(dp[k]-dp[j])/(S[j]-S[k])-a*S[j]-a*S[k]+b)/(-2*a);
}

int main() {
	setIO("test"); 
	
	n = gi;
	a = gi,b = gi,c = gi;
	
	S[0] = 0;
	For(i,1,n) S[i] = S[i-1] + gi;
	
	int l = 0,r = 1;
	Q[0] = 0;dp[0] = 0;
	For(i,1,n) {
		while (l + 1 < r && T(Q[l],Q[l+1]) < S[i]) ++ l;
		dp[i] = dp[Q[l]] + a*sqr(S[i]-S[Q[l]]) + b*(S[i]-S[Q[l]]) + c;
		while (l + 1 < r && T(Q[r-2],Q[r-1]) >= T(Q[r-1],i)) -- r;
		Q[r++] = i;
	}
	
	printf("%lld\n", dp[n]);
	
	return 0;
}
