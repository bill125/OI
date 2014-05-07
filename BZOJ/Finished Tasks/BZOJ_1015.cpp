/*
  Task: BZOJ_1015
  Created: 2012.03.10
  Author: Zhu Jiahao
*/
#include<cstdio>
#include<cstring>

using namespace std;

#define rep(i,n) for (i = 0;i < n;++i)
#define repD(i,n) for (i = n-1;i >= 0;--i)
#define fill(a,b) memset(a,b,sizeof(a))
#define ForE(i,a) for (i = a;i != 0;i = next[i])

const int maxN = 400000+10,maxM = 200000+10;
int i,j,k,N,M,K,x,y,cnt,ans;
int D[maxM],f[maxN],e[maxM*2],next[maxM*2],h[maxN];
bool v[maxN];

void addedge(int x,int y)
{
 	 e[++cnt] = y;next[cnt] = h[x];h[x] = cnt;
}

int getfather(int x)
{
 	if (f[x] != x) f[x] = getfather(f[x]);
 	return f[x];
}

void merge(int x,int y)
{
 	 if (x == y) return;
 	 if (rank[x] == rank[y]) ++rank[x];
 	 if (rank[x] > rank[y]) f[y] = x;
 	 else f[x] = y;
}

int main()
{
 	freopen("input.txt" , "r" , stdin);
 	freopen("output.txt" , "w" , stdout);
 	
 	scanf("%d %d", &N, &M);
 	rep(i,N) f[i] = i;
 	rep(i,M) {
	  scanf("%d %d", &x, &y);
	  addedge(x,y);addedge(y,x);
	}
	scanf("%d", &K);
	fill(v,false);
	rep(i,M) scanf("%d", &D[i]),v[D[i]] = true;
	rep(i,M) {
	  if (!v[i]) {
        x = getfather(i);
        ForE(j,h[i]) y = getfather(e[j]),Merge(getfatheri,e[j]);
      }
	repD(i,M) {
      merge(
    }
 	
 	return 0;
}
