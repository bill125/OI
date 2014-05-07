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

const int inf = ~0U>>1,maxn = 200,maxm = 200000;
int n,m,x[4]={1,-1,0,0},y[4]={0,0,-1,1};
int f[4][maxn][maxn],qk[maxm],qx[maxm],qy[maxm];
bool t[maxn][maxn],v[4][maxn][maxn];

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
	
	n = gI,m = gI;
	char c;
	rep(i,n) {
		rep(j,m) {
			c = getchar();
			t[i][j] = c=='B';
	//		printf("%c",c);
		}
	//	printf("\n");
		scanf("\n");
	}
	

	rep(i,n) rep(j,m) if (t[i][j]) {
		int l = -1,r = -1;
		rep(a,n) rep(b,m) rep(k,4) f[k][a][b] = inf;
		rep(k,4) {
			f[k][i][j] = 0;++r;
			qx[r] = i,qy[r] = j,qk[r] = k;
		}
		fill(v,0);
		while (l^r) {
			l=l%maxm+1;
			rep(k,4) {
				int dx=qx[l]+x[k],dy=qy[l]+y[k];
				if (t[dx][dy] && f[qk[l]][qx[l]][qy[l]]+(k!=qk[l])<f[k][dx][dy]) {
					f[k][dx][dy] = f[qk[l]][qx[l]][qy[l]]+(k!=qk[l]);
					if (!v[k][dx][dy]) {
						v[k][dx][dy] = true;
						r = r%maxm+1;
						qx[r] = dx,qy[r] = dy,qk[r] = k;
					}
				}
			}
			v[qk[l]][qx[l]][qy[l]] = false;
		}
	
		rep(a,n) rep(b,n) if (t[a][b]) {
			int now = inf;
			rep(k,4) now = min(now,f[k][a][b]);
			if (now > 1) {
				printf("NO\n");return 0;
			}
		}
	}
	
	printf("YES\n");
	
	return 0;
}
