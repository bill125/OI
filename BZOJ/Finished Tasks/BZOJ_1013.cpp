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

const int inf = ~0U>>1,maxn = 10+10;
int n;
db a[maxn][maxn];

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

void debug(int *a,int n) {rep(i,n) printf("%d ", a[i]);puts("");}

int main() {
	setIO("test"); 
	
	n = gi;
	rep(i,n+1) rep(j,n) scanf("%lf", &a[i][j]);
	
	rep(i,n) {
		a[i][n] = 0;
		rep(j,n) {
			a[i][n] += sqr(a[i][j])-sqr(a[n][j]);
		}
		rep(j,n) a[i][j] = 2*(a[i][j]-a[n][j]);
	}
	
	rep(i,n) {
		int j = i;
		while (j < n && 0==a[j][i]) ++j;
		if (j == n) continue;
		rep(k,n+1) swap(a[i][k],a[j][k]);
		For(k,i+1,n-1) {
			db t = a[k][i]/a[i][i];
			For(j,i,n) a[k][j] -= t*a[i][j];
		}
	}
	
	repD(i,n) {
		For(j,i+1,n-1) a[i][n] -= a[i][j]*a[j][n];
		a[i][n] /= a[i][i];
	}
	
	rep(i,n) {
		printf("%.3f", a[i][n]);
		if (i == n-1) puts("");
		else printf(" ");
	}
	
	return 0;
}
