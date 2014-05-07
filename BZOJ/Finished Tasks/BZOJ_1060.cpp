/*
  Task: BZOJ_1060
  Created: 2012.04.21
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

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
#define lowbit(x) ((x) & -(x))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int maxN = 500000+10,maxM = 1000000+10,INF = 2147483647;
int N,S,cnt;
int h[maxN],q[maxN],F[maxN];
bool v[maxN],End[maxN];
ll T[maxN],e[maxN];
struct Edge
{
 	   int next,to,len;
}E[maxM];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void addedge(int a,int b,int c)
{
 	 ++cnt;
 	 E[cnt].next = h[a];h[a] = cnt;E[cnt].to = b;E[cnt].len = c;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d", &N);
 	scanf("%d", &S),--S;
 	int a,b,c;
 	rep(i,N) h[i] = -1;
	rep(i,N-1) {
      scanf("%d %d %d", &a, &b, &c),--a,--b;
      addedge(a,b,c),addedge(b,a,c);
	}
	fill(v,0);
	int l = -1,r = 0;
	ll Time = -1;
	q[0] = S,v[S] = true,e[S] = 0;
	while (l < r) {
      End[q[++l]] = true;
      ForE(i,h[q[l]]) {
	    int j = E[i].to;
	    if (!v[j]) {
          End[q[l]] = false;
	      q[++r] = j;v[j] = true;
	      T[j] = T[q[l]] + E[i].len;
	      Time = max(T[j],Time);
	      F[j] = q[l];
        }
      }
    }
    repD(i,N) 
      if (!End[i]) T[i] = INF;
      else T[i] = Time-T[i];
    T[S] = 0;
    ForD(i,N-1,1) {
      int j = F[q[i]];
      T[j] = min(T[j],T[q[i]]);
      ForE(j,h[q[i]]) if (E[j].to != F[q[i]]) T[E[j].to] -= T[q[i]];  
    }	  
    ll ans = 0;
    rep(i,N) ans += T[i];
    printf("%lld\n", ans);
	
	return 0;
}
