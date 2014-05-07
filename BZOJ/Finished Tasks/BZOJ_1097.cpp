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
#define formap(i,e) for (map<int,int>::const_iterator i = e.begin();i != e.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()

const int inf = ~0U>>1,maxn = 20000+10,maxe = 400000+10,maxM = 1<<21;
int n,m,tot = -1,k,_n,cnt = 0;
int h[maxn],a[maxn],b[maxn],q[maxn],f[23][maxn],dp[23][maxM];
int vor[maxn],nach[maxn],two[maxM];
bool v[maxn],legal[23][maxM];

struct Edge {
	int next,to,len;
}E[maxe];

void setIO(string name)
{
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
	#endif
}

int gI()
{
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

void addedge(int a,int b,int c) {
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot,E[tot].len = c;
}

void spfa(int k) {
	int l = -1,r = 0;
	fill(v,0);
	q[0] = k;f[k][k] = 0;v[k] = true;
	while (l^r) {
		l = (l+1) % maxn;;
		ForE(i,q[l]) {
			int j = E[i].to;
			if (f[k][q[l]] + E[i].len < f[k][j]) {
				f[k][j] = f[k][q[l]] + E[i].len;
				if (!v[j]) {
					q[r = (r+1)%maxn] = j;
					v[j] = true;
				}
			}
		}
		v[q[l]] = false;
	}
}

int work(int x,int m) {
	if (m == (1<<k)-1) return f[x][n-1];
	int & t = dp[x][m],m2 = (1<<k)-1-m,i;
	while (m2) {
		i = two[m2&(-m2)]+1,m2-=m2&(-m2);
		if (legal[i][m|(1<<i-1)]) {
			if (dp[i][m|(1<<i-1)] == 1000000000) dp[i][m|(1<<i-1)] = work(i,m|(1<<i-1));
			t = min(t,dp[i][m|(1<<i-1)]+f[x][i]);
		}
	}
	
	return t;
}

int main()
{
	setIO("test"); 
	
	scanf("%d %d %d", &n, &m, &k);
	
	rep(i,21) two[1<<i] = i;
	rep(i,n) h[i] = -1;
	rep(i,m) {
		int a = gi-1,b = gi-1,c = gi;
		addedge(a,b,c),addedge(b,a,c);
	}
	
	int g = gi;
	rep(i,g) {
		int a = gi-1,b = gi-1;
		vor[b] |= 1<<a-1;
		nach[a] |= 1<<b-1;
	}
	rep(i,k+1) rep(j,n) f[i][j] = 1000000000;
	rep(i,k+1) spfa(i); 
	
	rep(i,k+1) rep(j,(1<<k)) dp[i][j] = 1000000000;
	For(i,1,k) rep(j,(1<<k)) 
		if (((1<<i-1)&j) && ((vor[i]&j)==vor[i]) && !(nach[i]&j)) legal[i][j] = true;
		else legal[i][j] = false;
	
	
	printf("%d\n", work(0,0));
		
	return 0;
}
