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

const int inf = ~0U>>1,maxn = 100000+10;
int n,m;
int a[maxn],b[maxn];
struct Element {
	int H,T,len;
}S[maxn];

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

void debug(int *a,int n) {rep(i,n) printf("%d ", a[i]);puts("");}
void debug(ll *a,int n) {rep(i,n) printf("%lld ", a[i]);puts("");}

int ok(int k) {
	rep(i,n) b[i] = a[i];
	int r = 1,cnt = 0;
	S[0].H = S[0].T = b[0];S[0].len = 1;
	For(i,1,n-1) {
		if (b[i] - k > S[r-1].T) {
			cnt += b[i] - k - S[r-1].T;
			b[i] = S[r-1].T + k;
		}
		S[r].H = S[r].T = b[i],S[r].len = 1,++r;
		while (r > 1 && S[r-1].H + k <= S[r-2].T) {
			cnt += (S[r-2].T - S[r-1].H - k) * S[r-2].len;
			S[r-2].H -= S[r-2].T - S[r-1].H - k;
			S[r-2].T = S[r-1].T;
			S[r-2].len += S[r-1].len;
			--r;
		}
	}
	
	int p = 0;
	rep(i,r) 
		if (S[i].len == 1) {
			b[p++] = S[i].H;
		}
		else {
			int d = (S[i].T - S[i].H) / (S[i].len - 1),now = S[i].H;
			rep(j,S[i].len) 
				b[p++] = now,
				now += d;
		}
	
	int t = cnt;
	rep(i,n) {
		cnt = t + b[i];
		for (int now = k,j = i+1;j < n && b[j] > now;++j) {
			cnt += b[j] - now;
			now += k;
		} 
		for (int now = k,j = i-1;j && b[j] > now + k;--j) {
			cnt += b[j] - now;
			now += k;
		}	
		if (cnt <= m) return i;
	}
	return -1;
}

int main() {
	setIO("test"); 
	
	n = gi;
	rep(i,n) a[i] = gi;
	
	int l = -1,r = 1000000000;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (ok(mid) != -1) r = mid;
		else l = mid;
	}
	
	printf("%d %d\n", r, ok(r)+1);
	
	return 0;
}
