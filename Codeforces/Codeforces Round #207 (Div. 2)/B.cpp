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

const int inf = ~0U>>1,maxl = 1000000+10;
ll n,m,l1,l2;
char c1[maxl],c2[maxl];
ll cnt[maxl][26],sum[maxl];

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

void pI(ll a) {
	if (a == 0){
		putchar(0);
		return ;
	}
	char c[20];
	int l = 0;c[0] = 0;
	
	for (;a;a/=10) c[l++] = a%10;
	repD(i,l) putchar(c[i]);
}

template <class T> void debug(const T &a,const int &n) {rep(i,n) cout << a[i] << " ";puts("");}

int gcd(int a,int b) {
	if (a == 0) return b;
	return gcd(b %a ,a);
}

int main() {
	setIO("test"); 
	
	n = gi,m = gi;
	scanf("%s",c1);
	scanf("%s",c2);
	l1 = strlen(c1);
	l2 = strlen(c2);
	int k = gcd(l1,l2);
	fill(cnt,0);
	rep(i,l1) ++cnt[i%k][c1[i]-'a'];
	rep(i,k) {
		sum[i] = 0;
		rep(j,26) sum[i] += cnt[i][j];
	}
	
	ll ans = 0;
	rep(i,l2) {
		ans += sum[i%k] - cnt[i%k][c2[i]-'a'];
	}
	ans *= m/(l1/k);
	printf("%lld\n", ans);
	
	return 0;
}
