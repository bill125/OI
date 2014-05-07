/*
  Task: BZOJ_1052
  Created: 2012.04.18
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

const int INF = 2147483647,maxN = 20000+10;
int N;
int X[maxN],Y[maxN],Ex[3][4],P[2][4][2];
bool v[maxN],t[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void GetExtrem(int x)
{
 	 Ex[x][0] = Ex[x][2] = -INF;Ex[x][1] = Ex[x][3] = INF;
 	 rep(i,N) 
       if (v[i]) {
         Ex[x][0] = max(Ex[x][0],X[i]),Ex[x][2] = max(Ex[x][2],Y[i]);
         Ex[x][1] = min(Ex[x][1],X[i]),Ex[x][3] = min(Ex[x][3],Y[i]);
	   }
}

void GetP(int x,int L,int A[]) 
{
 	 P[x][0][0] = A[0]-L;P[x][0][1] = A[2]-L;
 	 P[x][1][0] = A[0]-L;P[x][1][1] = A[3];
	 P[x][2][0] = A[1];P[x][2][1] = A[2]-L;
	 P[x][3][0] = A[1];P[x][3][1] = A[3];
}

void Clean(int x,int y,int L)
{
 	 rep(i,N) 
	   if (v[i] && X[i] >= x && X[i] <= x+L && Y[i] >= y && Y[i] <= y+L)
	     v[i] = false;
}

bool check(int L)
{
 	 int a,b;
 	 fill(v,true);
 	 GetExtrem(0);GetP(0,L,Ex[0]);
 	 rep(i,4) {
	   Clean(P[0][i][0],P[0][i][1],L);
	   GetExtrem(1);GetP(1,L,Ex[1]);
       rep(k,N) t[k] = v[k];
	   rep(j,4) {
	     rep(k,N) v[k] = t[k];
         Clean(P[1][j][0],P[1][j][1],L);
         GetExtrem(2);
         if (Ex[2][0] == -INF || (Ex[2][0]-Ex[2][1] <= L && Ex[2][2]-Ex[2][3] <= L)) return true; 
       }
       fill(v,true);
     }
     return false;
}

int main()
{
 //	setIO("test");
 	
 	scanf("%d", &N);
 	rep(i,N) scanf("%d %d", &X[i], &Y[i]);
	int l = -1,r = 2000000000;
	while (l + 1 < r) {
      int mid = (l+r)/2;
      if (check(mid)) r = mid;
      else l = mid;
	} 
	printf("%d\n", r);
	
	return 0;
}
