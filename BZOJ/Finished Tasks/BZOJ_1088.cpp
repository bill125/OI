/*
  Task: BZOJ_1088
  Created: 2012.07.02
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

const int maxN = 10000+10,INF = 2147483647;
int N;
int A[maxN],F[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int main()
{
 //	setIO("test");
 	
 	scanf("%d", &N);
 	rep(i,N) scanf("%d", &F[i]);
 	
    int ans = 0; 
    rep(k,2) {
      A[0] = k,A[1] = F[0]-A[0];
      For(j,1,N-2) A[j+1] = F[j] - A[j] - A[j-1];
      bool flag = A[N-1]+A[N-2] == F[N-1];
      rep(i,N) if (A[i] < 0 || A[i] > 1) {
        flag = false; break;
      }
      ans += flag;
    }
    
    printf("%d\n", ans);
     
	return 0;
}
