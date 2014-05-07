/*
  Task: BZOJ_1066
  Created: 2012.06.20
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

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
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int INF = 2147483647,maxR = 20+10,maxC = 20+10,maxN = 800+10;
int R,C,D,N,delta,S,T; 
int f[maxN][maxN],d[maxN],q[maxN];
bool v[maxN][maxN]; 

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int code(int a,int b)
{
 	return a*C+b+1;
}

bool Build()
{
 	 rep(i,T+1) d[i] = INF; 
	 d[S] = 0,q[0] = S;
	 int l = -1,r = 0; 
     while (l < r) {
       ++l; 
       rep(i,T+1)
	     if (f[q[l]][i] && d[q[l]] + 1 < d[i]) {
		   d[i] = d[q[l]] + 1;
		   if (i == T) return true;
		   q[++r] = i;
         } 
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
	   if (f[x][i] && d[x] + 1 == d[i] && Find(i,min(now_flow,f[x][i]))) {
	     f[x][i] -= delta,f[i][x] += delta;
	     return true;
	   }
     return false;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %d %d", &R, &C, &D);
 	N = R*C,S = 0,T = 2*N+1;
    rep(i,R) rep(j,C) rep(a,R) rep(b,C) 
	  if (abs(a-i) + abs(b-j) <= D) {
	  	int t1 = code(i,j),t2 = code(a,b); 
	    f[t1+N][t2] = INF;
      }
    char c;
    fill(v,false);
	rep(i,R) {
      scanf("\n");
	  rep(j,C) {
	    int t = code(i,j);
	    if (i - D < 0 || i + D >= R || j - D < 0 || j + D >= C) f[t+N][T] = INF;
	    c = getchar();
	    f[t][t+N] = c - '0';
	  } 
    }
    
    int ans = 0;
    rep(i,R) {
      scanf("\n");
      rep(j,C) {
        c = getchar();
	    if (c == 'L') {
  	      int t = code(i,j);
	      f[S][t] = 1;
	      ++ans;
	    }
	  }
    } 
    
    while (Build())
      while (Find(S,INF))
        ans -= delta;
    
	printf("%d\n", ans);
	
	return 0;
}
