/*
  Task: BZOJ_1003
  Created: 2012.02.21
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>

using namespace std;

#define For(i,a,b) for (i = a;i <= b;++i)
#define ForEdge(i,a) for (i = a;i != 0;i = next[i])
#define fill(a,b) memset(a,b,sizeof(a));

const int Maxint = 2147483647;
int i,j,k,K,n,m,E,x,y,z,d,l,r,cnt = 0,e[1000],h[50],dp[100],next[1000],len[1000],cost[110][110],Free[100][110],sub[100][110],use[50],q[10000],f[50];
bool v[50];

void Push(int x)
{
 	 if (v[x]) return;
 	 q[++r] = x;v[x] = 1;
}

void addedge(int a,int b,int c)
{
 	 len[++cnt] = c;next[cnt] = h[a];h[a] = cnt;e[cnt] = b;
}

int min(int a,int b)
{
 	if (a < b) return a;
 	else return b;
}

int Find(int Ltime,int Rtime)
{
 	fill(v,0);
 	int i,t;
 	For(i,1,m) f[i] = Maxint;
 	For(i,1,m) use[i] = sub[i][Rtime]-sub[i][Ltime-1] == Rtime-Ltime+1;
    l = 0;r = 1;q[1] = 1;f[1] = 0;v[1] = 1;
 	while (l < r) {
      ++l;
      for (t = h[q[l]];t != 0;t = next[t])
        if (use[e[t]] && f[q[l]] + len[t] < f[e[t]]) {
		  f[e[t]] = f[q[l]] + len[t];
          if (!v[e[t]]) {
		    q[++r] = e[t];v[e[t]] = 1;
		  }
		}
      v[q[l]] = 0;
	}
	return f[m];
}

int main()
{
 	fill(sub,0);fill(h,0);fill(next,0);fill(e,0);
	scanf("%d%d%d%d", &n, &m, &K, &E);
 	For(i,1,E) {
      scanf("%d%d%d", &x, &y, &z);
      addedge(x,y,z);addedge(y,x,z);
	} 
	fill(Free,1);
	scanf("%d", &d);
    For(i,1,d) {
      scanf("%d%d%d", &x, &y, &z); 
      For(j,y,z) Free[x][j] = 0;
    } 
    For(i,1,m) {
      sub[i][0] = 0;
	  For(j,1,n)  {
	    sub[i][j] = sub[i][j-1];
	    if (Free[i][j]) ++sub[i][j];

	  }
	} 
	For(i,1,n) For(j,i,n) cost[i][j] = Find(i,j);
	dp[0] = -K;
	For(i,1,n) {
      dp[i] = Maxint;
	  For(j,0,i-1) 
	    if (cost[j+1][i] != Maxint) {
		  dp[i] = min(dp[i],dp[j] + cost[j+1][i]*(i-j) + K);
		  
	}
	printf("%d\n", dp[n]);
 	return 0;
}
