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

const int inf = ~0U>>1;
int a[3][3],x[5]={0,-1,1,0,0},y[5]={0,0,0,-1,1},f[3][3];

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
	
	int n = 3;
	rep(i,n) rep(j,n) a[i][j] = gI%2;
	//rep(i,n) rep(j,n) printf("%d\n", a[i][j]);
	rep(i,n) rep(j,n) f[i][j] = 1;
	rep(i,n) rep(j,n) if (a[i][j]) 
		rep(k,5) {
			int dx = x[k]+i,dy = y[k]+j;
			if (dx>=0&&dx<3&&dy>=0&&dy<3) 
			  f[dx][dy] = 1-f[dx][dy];
		}
	rep(i,n) {
		rep(j,n) printf("%d",f[i][j]);
		printf("\n");
	}
	
	return 0;
}
