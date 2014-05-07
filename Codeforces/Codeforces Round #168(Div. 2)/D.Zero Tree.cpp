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

const int inf = ~0U>>1,maxn = 100000+10,maxe = 200000+10;
int n,tot = -1;
int q[maxn],h[maxn],f[maxn];
ll Plus[maxn],Minus[maxn],sum[maxn];
bool v[maxn];
struct Edge
{
	int next,to;
}E[maxe*2];

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

void addedge(int a,int b)
{
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot;
}
 
int main()
{
	//setIO("test"); 
	
	cin >> n;
	rep(i,n) h[i] = -1;
	rep(i,n-1) {
		int a,b;
		cin >> a >> b;--a,--b;
		addedge(a,b),addedge(b,a);
	}
	
	fill(v,0);
	int r = 1;f[0] = 0,q[0] = 0,v[0] = true;
	rep(i,n) ForE(j,q[i]) if (!v[E[j].to]) {
		v[E[j].to] = true;
		q[r++] = E[j].to,f[E[j].to] = q[i];
	}
	//rep(i,n) printf("%d ",q[i]);
	//printf("\n");
	fill(sum,0);
	rep(i,n) {
		ll a;cin >> a;
		Plus[i] = Minus[i] = 0;sum[i] = a;
	}
	
	repD(i,n) {
		int k = q[i];
		sum[k] += Plus[k]-Minus[k];
		if (sum[k]>0) Minus[k]+=sum[k]; 
		if (sum[k]<0) Plus[k]+=-sum[k];
		Plus[f[k]] = max(Plus[f[k]],Plus[k]);
		Minus[f[k]] = max(Minus[f[k]],Minus[k]);
	}
	ll ans = Plus[0] + Minus[0];
	cout << ans << endl;
	
	return 0;
}
