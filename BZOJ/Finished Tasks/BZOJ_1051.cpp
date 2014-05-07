/*
  Task: BZOJ_1051
  Created: 2012.04.17
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

const int maxN = 10000+10,maxM = 50000+10,INF = 2147483647;
int N,M,Dindex,Stop,Bcnt;
struct Edge
{
 	   int x,to,next;
}E[maxM];
int h[maxN],DFN[maxN],LOW[maxN],Stack[maxN],Belong[maxN],d[maxN],cnt[maxN];
bool InStack[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void addedge(int x,int y,int k)
{
 	 E[k].x = x;E[k].to = y;E[k].next = h[x];h[x] = k;
}

void Tarjan(int x)
{
 	 LOW[x] = DFN[x] = ++Dindex;
 	 Stack[++Stop] = x;
 	 InStack[x] = true;
 	 ForE(i,h[x]) {
	   int j;
	   j = E[i].to;
	   if (!DFN[j]) {
	     Tarjan(j);
	     if (LOW[j] < LOW[x]) LOW[x] = LOW[j];
       }
       else if (InStack[j] && DFN[j] < LOW[x]) LOW[x] = DFN[j];
     }
     if (LOW[x] == DFN[x]) {
       int j;
	   ++Bcnt;
       do {
   	     j = Stack[Stop--];
   	     InStack[j] = false;
   	     Belong[j] = Bcnt;
	   } while (x != j);
	 }
}

int main()
{
 //	setIO("test");
 	
 	scanf("%d %d", &N, &M);
 	int x,y;
 	rep(i,N) h[i] = -1;
    rep(i,M) scanf("%d %d", &x, &y),addedge(--x,--y,i);
    Stop = Bcnt = Dindex = 0;
	fill(DFN,0),fill(InStack,false);
	rep(i,N) 
	  if (!DFN[i]) Tarjan(i);
	fill(d,0),fill(cnt,0);
	rep(i,N) ++cnt[Belong[i]];
	rep(i,M) if (Belong[E[i].x] != Belong[E[i].to]) ++d[Belong[E[i].x]];
    int ans = 0;
    For(i,1,Bcnt) if (d[i] == 0) 
      if (ans != 0) {
 	    ans = 0; break;
      }
	  else ans = cnt[i];
    printf("%d\n", ans);
	
	return 0;
}
