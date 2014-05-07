/*
  Task: A. Two Problems
  Created: 2012.07.03
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

const int INF = 2147483647;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int main()
{
 	//setIO("test");
    
    int x,t,a,b,da,db;
    scanf("%d %d %d %d %d %d", &x, &t, &a, &b, &da, &db);
    bool flag = false;
    rep(i,t) rep(j,t) 
      if (a + b - da*i - db*j == x) {
        flag = true; break;
      } 
    rep(i,t) if (a - da*i == x) flag= true;
    rep(i,t) if (b - db*i == x) flag = true;
    if (x == 0) flag = true;
    if (flag) printf("YES\n");
    else printf("NO\n");
    
	return 0;
}
