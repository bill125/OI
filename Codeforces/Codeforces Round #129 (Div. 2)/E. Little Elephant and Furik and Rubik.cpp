/*
  Task: E. Little Elephant and Furik and Rubik
  Created: 2012.07.12
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef double db;
typedef long double ld;
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

const int INF = 2147483647,maxN = 200000+10;
int N;
char A[maxN],B[maxN];
ll cnt[26+10],cnt2[26+10];
db f[maxN];

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
 	
 	scanf("%d\n", &N);
 	scanf("%s\n", A);
    scanf("%s\n", B); 
    
    rep(i,26) cnt[i] = cnt2[i] = 0;
    
    ll a = 0,i;
    for (i = 1;i <= N;++i) {
      ll t = i*i;a += t;
    }
     
    f[0] = 0;
    rep(i,N) {
      f[i+1] = f[i] + (db)cnt2[A[i]-'A']/a*(N-i) + (db)cnt[B[i]-'A']/a*(N-i);
      if (A[i] == B[i]) f[i+1] += (db)(i+1)/a*(N-i);
      cnt[A[i]-'A'] += i+1;cnt2[B[i]-'A'] += i+1;
    }
    
    printf("%.6lf\n", f[N]);
  
    
	return 0;
}
