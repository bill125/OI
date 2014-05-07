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

const int inf = ~0U>>1;
int n;
int cnt[5];

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

int main() {
	setIO("test"); 
	
	n = gi;
	int all = 0;
	rep(i,n) {
		int k = gi;
		if (k != 0) ++cnt[k];
		all += k;
	}
	if (all == 1 || all == 2 || all == 5) {
		puts("-1");
		return 0;
	}
	
	int ans = 0;
	if (cnt[1] <= cnt[2]) {
		ans = cnt[1];
		cnt[2] -= cnt[1];
		ans += (cnt[2]/3)*2;
		cnt[2] %= 3;
		if (cnt[2]>0) 
		if (cnt[4] >= cnt[2]) ans += cnt[2];
		else {
			ans += 2;
		}
	}
	else {
		ans += cnt[2];
		cnt[1] -= cnt[2],cnt[2] = 0;
		ans += (cnt[1]/3)*2;cnt[3] += cnt[1]/3;
		cnt[1] %= 3;
		if (cnt[1] > 0) 
			if (cnt[3] >= cnt[1]) {
				ans += cnt[1];
			}
			else {
				ans += 2;
			}
	}
	printf("%d\n", ans);
	
	return 0;
}
