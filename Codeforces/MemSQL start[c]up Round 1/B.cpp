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
typedef unsigned long long ull;
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

const int inf = ~0U>>1,maxall = 10000000;
ull n,ans[maxall];
int all = 0;

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

ull min(ull a,ull b) {
	if (a<b) return a;
	else return b;
}

int main() {
	setIO("test"); 
	
	cin >> n;
	For(i,0,63) {
		ull t = (ull)pow(2,i)-1;
		ull A = 2,B = 2*t+1, C = t;
		ull l = 0,r = min(1000000000,(n-C)/B+1);
		while (l + 1 < r) {
			ull x=(ull)(l+r)/2;
			if (A*x*x+B*x+C<=n) l = x;
			else r = x;
		}
		
		if (A*l*l+B*l+C == n) {
			ans[all++] = (ull)(2*l+1)*(ull)pow(2,i);
		}
	}
	if (all==0) puts("-1");
	else {
		sort(ans,ans + all);
		rep(i,all) cout << ans[i] << endl;
	}
		
	return 0;
}
