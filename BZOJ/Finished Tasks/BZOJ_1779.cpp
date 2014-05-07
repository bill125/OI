/*
  Task:
  Created:
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
#define ForE(i,a) for (int i = a;i != 0;i = E[i].next)
#define sqr(a) (a*a)
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(x) (x & -x)
#define abs(x) (x > 0 ? x : -x)
#define pb push_back

const int maxN = 1000+10,maxP = 1000+10,maxM = 10000+10,INF = 2147483647;
int V,M,S,T,cnt,delta;
int h[maxN],d[maxP],q[maxP*10],f[maxN][maxN],mark[maxN];
bool v[maxP];
char c;
struct Edge
{
 	   int to,next;
}E[maxM];
struct Cows
{
 	   int cnt,pos[maxN],num[maxN];
}Tom,John;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void addedge(int x,int y)
{
 	 E[++cnt].next = h[x];h[x] = cnt;E[cnt].to = y;
}

bool Build()
{
 	 rep(i,T+1) d[i] = INF;
 	 fill(v,0);
 	 int l = -1,r = 0;
     q[0] = S,d[S] = 0;v[S] = true;
     while (l < r) {
       ++l;
       rep(i,T+1) 
	     if (f[q[l]][i] && d[q[l]] + 1 < d[i]) {
           d[i] = d[q[l]] + 1;
           if (!v[i]) {
  		     if (i == T) return true;
		     q[++r] = i;v[i] = true;
		   }
		 }
       v[q[l]] = false;
	 }
	 return false;
}

bool Find(int x,int now_flow)
{
 	 if (x == T) {
       delta = now_flow;
       return true;
	 }
	 rep(i,T+1) 
       if (d[x] + 1 == d[i] && f[x][i] && Find(i,min(now_flow,f[x][i]))) {
         f[x][i] -= delta;f[i][x] += delta;
         return true;
	   }
	 return false;
}

int main()
{
 	setIO("test");
 	
 	scanf("%d %d\n", &V, &M);
 	Tom.cnt = John.cnt = 0;
 	fill(v,false);
 	rep(i,V) {
	  c = getchar();
	  if (c == 'T') Tom.pos[Tom.cnt++] = i+1,v[i+1] = true;
	  if (c == 'J') John.pos[John.cnt++] = i+1;
    }
    int x,y;
    rep(i,M) {
      scanf("%d %d", &x, &y);
      addedge(x,y),addedge(y,x);
	}
	S = 0,T = V+1;
	fill(f,0);
	rep(i,John.cnt) {
      f[S][John.pos[i]] = 1;
	  ForE(j,h[John.pos[i]]) f[John.pos[i]][E[j].to] = 1;
	}
	rep(i,Tom.cnt) {
      f[Tom.pos[i]][T] = 1;
      ForE(j,h[Tom.pos[i]]) if (!v[E[j].to]) f[E[j].to][Tom.pos[i]] = 1;
    }
    int ans = 0;
    while (Build())
      while (Find(S,INF))
        ans += delta;
    printf("%d\n", ans);
	
	return 0;
}
