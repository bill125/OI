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

const int inf = ~0U>>1,maxn = 1000000+10;
int n;
char A[maxn],B[maxn];
int p[26],C[maxn];
ll S[maxn];

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

void Add(int x) {
	while (x <= n) {
		++S[x];
		x += lowbit(x);
	}
}

ll Sum(int x) {
	ll res = 0;
	while (x) {
		res += S[x];
		x -= lowbit(x);
	}
	return res;
}

int main() {
	setIO("test"); 
	
	scanf("%d", &n);
	scanf("%s", A);
	scanf("%s", B);
	//printf("%s\n", A);
	//printf("%s\n", B);
//	return 0;
	
	rep(i,26) {
		p[i] = 0;
		while (p[i] < n && B[p[i]] != i+'A') ++p[i];
	}
	//return 0;
	rep(i,n) {
		int t = A[i]-'A';
		C[i] = p[t]++;
		while (p[t] < n && B[p[t]] != A[i]) ++p[t];
	}
	
	//return 0;
	rep(i,n) ++C[i];
	ll ans = 0;
	rep(i,n) {
		ans += i-Sum(C[i]);
		Add(C[i]);
	}
	cout << ans << endl;
	
	
	return 0;
}
