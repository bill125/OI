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

const int inf = ~0U>>1,maxn = 250000+10;
int n,l = 0;
int Stack[maxn];

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

int Pop_Stack(int b) {
	int last = -1,cnt = 0;
	while (l && Stack[l] > b) {
		if (Stack[l] != last) ++ cnt;
		last = Stack[l--];
	}
	return cnt;
}

int main() {
	setIO("test"); 
	
	scanf("%d", &n);
	
	int ans = 0;
	rep(i,n) {
		int a = gi,b = gi;
		ans += Pop_Stack(b);
		Stack[++l] = b;
	}
	ans += Pop_Stack(-1);
	printf("%d\n", ans);
		
	return 0;
}
