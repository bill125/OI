/*
  Task: D. Choosing Capital for Treeland
  Created: 2012.08.27
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int INF = 2147483647,maxN = 200000+10,maxE = 400000+10;
int N,Ecnt = -1;
int h[maxN],d[maxN],cnt[maxN],q[maxN];
bool v[maxN];
struct Edge
{
	int to,next,len;
}E[maxE];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void addedge(int a,int b,int c)
{
	++Ecnt;
	E[Ecnt].next = h[a];h[a] = Ecnt;E[Ecnt].to = b;E[Ecnt].len = c;
}

int main()
{
 //	setIO("test"); 	
	 
	scanf("%d", &N);
	rep(i,N) h[i] = -1;
	rep(i,N-1) {
		int a,b;
		scanf("%d %d", &a, &b),--a,--b;
		addedge(a,b,1),addedge(b,a,0);
	}
	fill(v,0);
	q[0] = 0,v[0] = true,d[0] = 0,cnt[0] = 0;
	int r = 0,all = 0;
	rep(k,N) {
		int i = q[k];
		ForE(j,h[i]) if (!v[E[j].to]) {
			d[E[j].to] = d[i] + 1;
			cnt[E[j].to] = cnt[i] + 1-E[j].len;
			v[E[j].to] = true;
			q[++r] = E[j].to;
			all += 1-E[j].len;
		}
	}
	
	int ans = INF,anscnt = 0,ansq[maxN];
	rep(i,N) {
		int now = all - cnt[i] + (d[i] - cnt[i]);
		if (now < ans) {
			ans = now,anscnt = 1,ansq[0] = i+1;
		}
		else if (now == ans) ansq[anscnt++] = i+1;
	}
	printf("%d\n", ans);
	rep(i,anscnt) {
		printf("%d", ansq[i]);
		if (i == anscnt - 1) printf("\n");
		else printf(" ");
	}
    
	return 0;
}
