/*
  Task: D. Common Divisors
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

const int maxLen = 100000+10,INF = 2147483647;
char s1[maxLen],s2[maxLen];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int strlen(char c[])
{
 	rep(i,maxLen) if (c[i] == 0) return i;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%s\n", s1);
 	scanf("%s\n", s2);
 	int l1 = strlen(s1),l2 = strlen(s2);
 	int N = min(l1,l2);
 	int ans = 0;
	rep(i,N) {
      int j = i+1,k = 0;
      if (l1 % (i+1) != 0 || l2 % (i+1) != 0) continue;
      bool flag = true;
      while (j < l1) {
	    if (s1[j] != s1[k]) {
          flag = false;break;
        }
	    ++ k;++j;
	    if (k > i) k = 0;
      }
      if (!flag) continue;
      k = 0;
      rep(j,l2) {
        if (s2[j] != s1[k]){
		  flag = false;break;
        }
        ++ k;
        if (k > i) k = 0;
      }
      if (!flag) continue;
      ++ans;
	}
	printf("%d\n", ans);
	
	return 0;
}
