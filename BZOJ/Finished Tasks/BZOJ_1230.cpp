/*
  Task: BZOJ_1230
  Created: 2012.04.24
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

const int maxN = 300000,INF = 2147483647,maxN = 1000+10;
int N,M,h;
struct Tree
{
 	   int Sum,All;
       bool Tag;
}T[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void Pass_Down(int x)
{
	if (T[x].Tag) {
       int a = x*2,b = x*2+1;
       if (a < shl(1,h+1)) {
         T[a].Tag = !T[a].Tag;T[b].Tag = !T[b].Tag;
         T[a].Sum = T[a].All - T[a].Sum;
         T[b].Sum = T[b].All - T[b].Sum;
	   }
       T[x].Tag = false;
	}
}

void Pass_to_Leaf(int x)
{
 	 repD(i,h+1) Pass_Down(shr(x,i));
}

void Update(int x)
{
 	 x /= 2;
 	 while (x != 0) {
       T[x].Sum = T[x*2].Sum + T[x*2+1].Sum;
       x /= 2;
	 }
}

void Change(int x,int y)
{
 	int l = x+shl(1,h)-1,r = y+shl(1,h)+1;
 	Pass_to_Leaf(l),Pass_to_Leaf(r);
 	while (l + 1 < r) {
      if (l % 2 == 0) T[l+1].Sum = T[l+1].All-T[l+1].Sum,T[l+1].Tag = !T[l+1].Tag,Update(l+1);
      if (r % 2 == 1) T[r-1].Sum = T[r-1].All-T[r-1].Sum,T[r-1].Tag = !T[r-1].Tag,Update(r-1);
      l /= 2,r /= 2;
	}
}

int Ask(int x,int y)
{
 	int l = x+shl(1,h)-1,r = y+shl(1,h)+1;
 	Pass_to_Leaf(l),Pass_to_Leaf(r);
	int cnt = 0;
	while (l + 1 < r) {
      if (l % 2 == 0) cnt += T[l+1].Sum;
      if (r % 2 == 1) cnt += T[r-1].Sum;
      l /= 2,r /= 2;
    }
    return cnt;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %d", &N, &M);
	h = 2;
	while (shl(1,h) < N+2) ++h;
	rep(i,shl(1,h+1)) T[i].Sum = 0,T[i].Tag = false;
	rep(i,N) T[i+shl(1,h)+1].All = 1;
	repD(i,shl(1,h)) T[i].All = T[i*2].All + T[i*2+1].All; 
	int k,a,b;
	rep(i,M) {
      scanf("%d %d %d", &k, &a, &b);
      if (k == 0) Change(a,b);
      else printf("%d\n", Ask(a,b));
    }
	
	return 0;
}
