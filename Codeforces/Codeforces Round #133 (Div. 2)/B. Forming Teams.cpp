/*
  Task: B. Forming Teams
  Created: 2012.08.14
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

const int INF = 2147483647,maxN = 1000+10,maxE = 2000+10;
int N,M,tot = -1;
int h[maxN],d[maxN];
struct Edge
{
	int to,next;
}E[maxE];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void addedge(int a,int b)
{
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot;
}

int DFS(int x)
{
	--d[x];
	ForE(i,h[x]) if (d[E[i].to] == 2) {
		--d[E[i].to];
		return DFS(E[i].to)+1;
	}
	return 1;
}

void Clean(int x)
{
	--d[x];
	ForE(i,h[x]) if (d[E[i].to] != 0) {
		--d[E[i].to];
		if (d[E[i].to] != 0) Clean(E[i].to);
		return ;
	}
}

int main()
{
 	//setIO("test"); 	
	
    scanf("%d %d", &N, &M);
	rep(i,N) h[i] = -1,d[i] = 0;
	rep(i,M) {
		int a,b;
		scanf("%d %d", &a, &b);
		--a,--b;++d[a],++d[b];
		addedge(a,b),addedge(b,a);
	}
	int ans = 0;
	rep(i,N) if (d[i] == 1) Clean(i);
	rep(i,N) if (d[i] == 2) {
		int now = DFS(i);
		if (now % 2 == 1) ++ ans;
		--d[i];
	}
	if ((N-ans) % 2 == 1) ++ans;
	printf("%d\n", ans);
	
	return 0;
}
