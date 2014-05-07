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

const int inf = ~0U>>1;
int n;

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

int main() {
	setIO("test"); 
	
	scanf("%d", &n);
	ll X1 = inf,Y1 = inf,X2 = -inf,Y2 = -inf;
	ll cnt = 0;
	rep(i,n) {
		ll x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cnt += (x2-x1)*(y2-y1);
		X1 = min(X1,x1);
		X2 = max(X2,x2);
		Y1 = min(Y1,y1);
		Y2 = max(Y2,y2);
	}
	if ((Y2-Y1)*(X2-X1)==cnt && Y2-Y1==X2-X1) puts("YES");
	else puts("NO");
		
	return 0;
}
