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
#define dis(x1,y1,x2,y2) sqrt(sqr(x1-x2)+sqr(y1-y2))

const int inf = ~0U>>1,maxn = 1000+10;
int n,m;
int x[maxn],y[maxn],a[maxn],q[maxn];
bool v[maxn];
db d[maxn][maxn];

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

bool ok(int maxd) {
	fill(v,0);
	int l = -1,r = 0;
	q[0] = 0;v[0] = 1;
	while (l < r) {
		++l;
		rep(i,n) 
			if (!v[i] && d[q[l]][i] <= maxd) {
				v[i] = 1;
				q[++r] = i;
			}
	}
	return r == n-1;
}

int main() {
	setIO("test"); 
	
	m = gi;
	rep(i,m) a[i] = gi;
	
	n = gi;
	rep(i,n) x[i] = gi,y[i] = gi;
	rep(i,n) rep(j,n) d[i][j] = (db)dis(x[i],y[i],x[j],y[j]);
	
	int l = 0,r = 1001;
	while (l + 1 < r) {
		int mid = (l+r) >> 1;
		if (ok(mid)) r = mid;
		else l = mid;
	}
	
	int ans = 0;
	rep(i,m) if (a[i] >= r) ++ans;
	printf("%d\n", ans);
	
	return 0;
}
