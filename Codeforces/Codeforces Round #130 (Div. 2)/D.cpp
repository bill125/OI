/*
  Task:
  Created:
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

const int INF = 2147483647,maxN = 50+10;
int N;
unsigned long long A[5],cnt[5],P[maxN];

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
	
	scanf("%d", &N);
	rep(i,N) cin >> P[i];
	ll sum = 0;
	rep(i,5) cin >> A[i],cnt[i] = 0;
	rep(i,N) {
		sum += P[i];
		repD(i,5) {
			ll k = sum / A[i];
			sum -= k*A[i];
			cnt[i] += k;
		}
	}
	rep(i,5) {
		cout << cnt[i];
		if (i == 4) printf("\n");
		else printf(" ");
	}
	cout << sum << endl;
    
	return 0;
}
