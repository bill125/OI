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
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define fill(a,b) memset(a,b,sizeof(a))
#define gI gi()

const int inf = ~0U>>1,maxn = 100000+10;
int n,k,ans = 0;
int A[maxn];
bool v[maxn];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int gi()
{
	char c = getchar();
	while (c != '-' && (c > '9' || c < '0')) c = getchar();
	int n = 0,s = 1;if (c == '-') s = -1,c = getchar();
	while (c >= '0' && c <= '9') n = n*10 + c - '0',c = getchar();
	return n*s;
}
 
int main()
{
	//setIO("test"); 
	
	n = gI,k = gI;
	rep(i,n) A[i] = gI;
	sort(A,A + n);
	//rep(i,n) printf("%d\n", A[i]);
	fill(v,0);
	repD(i,n) if (!v[i]) {
		++ans;
		int l = -1,r = i;
		if (A[i]%k!=0) continue;
		while (l+1<r) {
			int mid = (l+r)/2;
			if (A[mid]>A[i]/k) r = mid;
			else l = mid;
		}
		if (l!=-1&&A[l]==A[i]/k) v[l] = true;
	}
	printf("%d\n", ans);
	
	return 0;
}
