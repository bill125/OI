/*
  Task: BZOJ_1828
  Created: 2012.04.26
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

const int maxN = 220000+10,maxM = 100000+10,INF = 2147483647;
int N,M,h;
struct Request
{
 	   int A,B;
}Q[maxM];
struct Tree
{
 	   int Min,Tag;
}T[maxN*2];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool cmp(Request a,Request b)
{
 	 return a.A < b.A;
}

void Update(int x)
{
 	 x /= 2;
 	 while (x != 0) {
       T[x].Min = min(T[x*2].Min,T[x*2+1].Min);
       x /= 2;
	 }
}

void Pass_Down(int x)
{
 	 if (T[x].Tag != 0) { 
	   int a = x*2,b = x*2+1;
	   if (b <= shl(1,h+1)) {
         T[a].Tag += T[x].Tag,T[b].Tag += T[x].Tag;
         T[a].Min += T[x].Tag,T[b].Min += T[x].Tag;
       }
	   T[x].Tag = 0;
	 }
}

void Pass_to_Leaf(int x)
{
 	 repD(i,h+1) Pass_Down(shr(x,i));
}

bool Ask(int x,int y)
{
 	 int l = x-1+shl(1,h),r = y+1+shl(1,h);
 	 Pass_to_Leaf(l),Pass_to_Leaf(r);
	 while (l + 1 < r) {
       if (l % 2 == 0) if (T[l+1].Min == 0) return false;
       if (r % 2 == 1) if (T[r-1].Min == 0) return false;
       l /= 2,r /= 2;
	 }
	 return true;
}

void Add(int x,int y,int c)
{
 	 int l = x-1+shl(1,h),r = y+1+shl(1,h);
 	 Pass_to_Leaf(l),Pass_to_Leaf(r);
 	 int k = 0;
 	 while (l + 1 < r) {
       if (l % 2 == 0) T[l+1].Tag += c,T[l+1].Min += c,Update(l+1);
       if (r % 2 == 1) T[r-1].Tag += c,T[r-1].Min += c,Update(r-1);
	   l /= 2,r /= 2;
     } 
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %d", &N, &M);	
 	h = 2;
 	while (shl(1,h) < N+2) ++h;
 	int k;
 	rep(i,shl(1,h)) T[i+shl(1,h)].Min = INF;
 	rep(i,N) scanf("%d", &k),T[i+shl(1,h)+1].Min = k;
 	repD(i,shl(1,h)) T[i].Min = min(T[i*2].Min,T[i*2+1].Min);
	rep(i,shl(1,h+1)) T[i].Tag = 0;
 	rep(i,M) scanf("%d %d", &Q[i].A, &Q[i].B);
	sort(Q,Q + M,cmp);
	int ans = 0;
	repD(i,M) 
      if (Ask(Q[i].A,Q[i].B)) {
        Add(Q[i].A,Q[i].B,-1);
        ++ans;
	  }
    printf("%d\n", ans);
	
	return 0;
}
