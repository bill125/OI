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
#include <deque>
 
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

const int inf = ~0U>>1,maxn = 200+10;
int n,m,x,y,K;
bool f[maxn][maxn];
int s[maxn],t[maxn],d[maxn],dp[maxn][maxn][maxn];
deque<pair<int,int> > S;

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
void debug(ll *a,int n) {rep(i,n) cout << a[i] << " ";puts("");}

void Push(int pos,int x) {
	while (S.size()) {
		if (pos + x < S.back().first + S.back().second) break;
		S.pop_back();
	}
	S.pb(make_pair(pos,x)); 
}

int main() {
	setIO("test"); 
	
	n = gi,m = gi,x = gi-1,y = gi-1,K = gi;
	
	rep(i,n) {
		char c[maxn];
		scanf("%s", c);
		rep(j,m) f[i][j] = c[j] == '.';
	}
	rep(i,K) s[i] = gi,t[i] = gi,d[i] = gi-1;
	
	fill(dp,0);
	repD(k,K) {
		int T = t[k]-s[k]+1,p;
		if (d[k] == 0) {
			T = min(T,n);
			rep(j,m) {
				S.clear();
				p = n-1;
								
				repD(i,n) {
					if (!f[i][j]) S.clear(),p = i-1;
					else {
						while (p >= max(0,i-T) && f[p][j]) 
							Push(-p,dp[p][j][k+1]),--p;
						if (i < -S.front().first)
							S.pop_front();
						dp[i][j][k] = S.front().first + S.front().second + i;
					}
				}
			}
		}
		else if (d[k] == 1) {
			T = min(T,n);
			rep(j,m) {
				S.clear();
				p = 0;
				
				rep(i,n) {
					if (!f[i][j]) S.clear(),p = i+1;
					else {
						while (p <= min(n-1,i+T) && f[p][j]) 
							Push(p,dp[p][j][k+1]),++p;
						if (i > S.front().first)
							S.pop_front();
						dp[i][j][k] = S.front().first + S.front().second - i;	
					}
				}
			}
		}
		else if (d[k] == 2) {
			T = min(T,m);
			rep(i,n) {
				S.clear();
				p = m-1;
				
				repD(j,m) {
					if (!f[i][j]) S.clear(),p = j-1;
					else {
						while (p >= max(0,j-T) && f[i][p])
							Push(-p,dp[i][p][k+1]),--p;
						if (j < -S.front().first) 
							S.pop_front();
						dp[i][j][k] = S.front().first + S.front().second + j;
					}
				}
			}
		}
		else {
			T = min(T,m);
			rep(i,n) {
				S.clear();
				p = 0;
								
				rep(j,m) {
					if (!f[i][j]) S.clear(),p = j+1;
					else {
						while (p <= min(m-1,j+T) && f[i][p])
							Push(p,dp[i][p][k+1]),++p;
						if (j > S.front().first)
							S.pop_front();
						dp[i][j][k] = S.front().first + S.front().second - j;
					}
					
				}
			}
		}
	}

	printf("%d\n", dp[x][y][0]);
	
	return 0;
}
