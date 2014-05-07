/*
  Task: BZOJ_1050
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
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(x) ((x) & -(x))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int maxN = 500+10,maxM = 5000+10,INF = 2147483647;
int N,M,cnt = 0;
struct Edge
{
 	   int A,B,e;
 	   bool V;
}E[maxM];
int f[maxN],num[maxM],Rank[maxN];
bool map[maxN][maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void addedge(int x,int y,int v)
{ 
 	 E[cnt].A = x;E[cnt].B = y;E[cnt].e = v;
     cnt ++;
}

bool cmp(int a,int b)
{
 	 return E[a].e < E[b].e;
}

int Find(int x)
{
 	if (f[x] != x) f[x] = Find(f[x]);
 	return f[x];
}

void Merge(int x,int y)
{
 	 x = Find(x);y = Find(y);
 	 if (x == y) return;
 	 if (Rank[x] == Rank[y]) Rank[x] ++;
 	 if (Rank[x] < Rank[y]) f[x] = y;
 	 else f[y] = x;
}

int gcd(int a,int b)
{
 	 if (a < b) swap(a,b);
 	 if (b == 0) return a;
 	 return gcd(b,a % b);
}

int main()
{
 	//setIO("test");
	
	scanf("%d %d", &N, &M);
	int x,y,v,S,T;
	rep(i,M) scanf("%d %d %d", &x, &y, &v),addedge(--x,--y,v),num[i] = i;
	sort(num,num + M,cmp);
	fill(map,false);
    scanf("%d %d", &S, &T),--S,--T;
    int ansX = -1,ansY = INF;
	rep(i,M) {
      rep(j,N) f[j] = j;
      fill(Rank,0);
      int now = -1;
      bool flag = false;
      For(k,i,M-1) {
	    Merge(E[num[k]].A,E[num[k]].B);
	    now = E[num[k]].e;
	    if (Find(S) == Find(T)) {
          flag = true;break;
        }
	  } 
	  if (!flag) continue;
	  if (ansX == -1 || now*ansY  < ansX *E[num[i]].e ) {
        ansX = now;ansY = E[num[i]].e;
	  }
	}
	if (ansX == -1) printf("IMPOSSIBLE\n");
	else {
	  int k = gcd(ansX,ansY);
	  ansX /= k,ansY /= k;
	  printf("%d", ansX);
	  if (ansY != 1 || ansX != 1) printf("/%d\n", ansY);
	  else printf("\n");
    }
    
	return 0;
}
