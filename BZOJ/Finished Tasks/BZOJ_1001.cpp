#include<cstdio>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

#define maxn 1000000
#define scan(x) scanf("%d", &x);
#define For(i,a,b) for (i = a;i <= b;++i)
#define Rep(x) for (t = x;t != 0;t = next[t])
#define Push(x) q[++r] = x; 
#define fill(x,y) memset(x,y,sizeof(x));

const int Maxint = 2147483647;
int i,j,k,t,n,m,a,b,S,T,delta,ans = 0,cnt,num[maxn*3],e[maxn*6],d[maxn+100],q[maxn*6],next[maxn*6],h[maxn+100],len[maxn*6];
bool v[maxn+100];

int code(int x,int y)
{
 	 return ((x-1)*m+y);
}

void addedge(int x,int y,int l)
{
 	 ++cnt;
 	 next[cnt] = h[x];h[x] = cnt;e[cnt] = y;len[cnt] = l;
}

int main()
{
 	freopen("input.txt" , "r" , stdin);
 	freopen("output.txt" , "w" , stdout);
 	scan(n);scan(m);
 	S = 0;T = n*m+1; 
 	For(i,1,n) For (j,1,m-1) {
	  scan(k);
	  if (i == 1) addedge(S,code(i,j)*2,k);
	  else if (i == n) addedge(code(i,j)*2,T,k);
	  else addedge(code(i,j)*2,code(i,j+1)*2-1,k);
	}
    For (i,1,n-1) For (j,1,m) {
	  scan(k);
	  if (j == 1) addedge(S,code(
	  addedge(code(i,j),code(i+1,j),k,cnt+2);
	  addedge(code(i+1,j),code(i,j),0,cnt);
	}
	For (i,1,n-1) For (j,1,m-1) {
	  scan(k);
	  addedge(code(i,j),code(i+1,j+1),k,cnt+2);
	  addedge(code(i+1,j+1),code(i,j),0,cnt);
	}
    
    while (Build())
      while (Find(S,Maxint))
        ans += delta;
        
    printf("%d\n", ans);
 	
 	return 0;
}
