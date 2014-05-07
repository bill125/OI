/*
  Task: BZOJ_1067
  Created: 2012.06.21
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

const int INF = 2147483647,maxN = 50000+10,maxP = 140000;
int N,M,Y[maxN],R[maxN],h;
bool f1,f2;
struct Tree
{
 	   int Max;
}T[maxP];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int Get(int x)
{
 	int l = 0,r = N;
	while (l + 1 < r) {
      int mid = (l+r) / 2;
	  if (Y[mid] <= x) l = mid;
	  else r = mid;
	}
	return l;
}

int Ask(int a,int b)
{
 	++a,++b;
 	int l = a+shl(1,h)-1,r = b+shl(1,h)+1;
 	int tmp = 0;
 	while (l + 1 < r) {
      if (l % 2 == 0) tmp = max(T[l+1].Max,tmp);
      if (r % 2 == 1) tmp = max(T[r-1].Max,tmp);
      l /= 2,r /= 2;
	}
	return tmp;
}

int main()
{
 	setIO("test");
 	
 	scanf("%d", &N);
 	rep(i,N) scanf("%d %d", &Y[i], &R[i]); 
 	h = 1;
 	while (shl(1,h) < N+2) ++h;
 	scanf("%d", &M);
 	rep(i,N) T[i+shl(1,h)+1].Max = R[i];
 	ForD(i,shl(1,h)-1,1) T[i].Max = max(T[i*2].Max,T[i*2+1].Max);
 	rep(i,M) {
	  int a,b;
	  scanf("%d %d", &a, &b);
	  if (b <= a) {
 	    printf("false\n");continue;
      }
	  int x = Get(a),y = Get(b);
	  bool f1 = Y[x] == a,f2 = Y[y] == b;
	  if (Y[x] < a) ++x;
	  if (f1) 
	    if (f2) 
   		  if (R[x] > R[y] && Ask(x+1,y-1) < R[y]) 
 	 	    if (Y[y]-Y[x] == y-x) printf("true\n");
 	 	    else printf("maybe\n");
 	      else printf("false\n");
   		else 
		  if (Ask(x+1,y) >= R[x]) printf("false\n");
		  else printf("maybe\n");
      else 
	    if (f2) 
   		  if (Ask(x,y-1) >= R[y]) printf("false\n");
   		  else printf("maybe\n");
		else printf("maybe\n");
    }
	
	return 0;
}
