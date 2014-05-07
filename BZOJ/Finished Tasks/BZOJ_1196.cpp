/*
  Task: BZOJ_1196
  Created: 2012.08.12
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

const int INF = 2147483647,maxN = 10000+10,maxM = 20000+10;
int N,M,K;
int f[maxN],rank[maxN];
struct Edge
{
	int a,b,c1,c2;
}E[maxM];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int getfather(int x)
{
	if (f[x] != x) f[x] = getfather(f[x]);
	return f[x];
}

void Merge(int x,int y)
{
	if (rank[x] == rank[y]) ++rank[y];
	if (rank[x] > rank[y]) f[y] = x;
	else f[x] = y;
}

bool check(int Max)
{
	rep(i,N) f[i] = i,rank[i] = 0;
	int cnt = 0;
	rep(i,M) if (E[i].c1 <= Max) {
		int x = getfather(E[i].a),y = getfather(E[i].b);
		if (x != y) Merge(x,y),++cnt;
	}
	if (cnt < K) return false;
	if (cnt == N-1) return true;
	rep(i,M) if (E[i].c2 <= Max) {
		int x = getfather(E[i].a),y = getfather(E[i].b);
		if (x != y) {
			Merge(x,y),++cnt;
			if (cnt == N-1) return true;
		}
	}
	return false;
}

int main()
{
 	//setIO("test"); 	
	
	scanf("%d %d %d", &N, &K, &M);
	rep(i,M) scanf("%d %d %d %d", &E[i].a, &E[i].b, &E[i].c1, &E[i].c2),--E[i].a,--E[i].b;
	int l = 0,r = 30000;
	while (l + 1 < r) {
		int mid = (l+r) / 2;
		if (check(mid)) r = mid;
		else l = mid;
	}
	printf("%d\n", r);
    
	return 0;
}
