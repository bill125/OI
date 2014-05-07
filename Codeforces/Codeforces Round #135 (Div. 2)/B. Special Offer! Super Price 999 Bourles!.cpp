/*
  Task: B. Special Offer! Super Price 999 Bourles!
  Created: 2012.08.27
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

const int INF = 2147483647,maxL = 19 + 10;
ll P,P2,D;
ll a[maxL];

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
	
	a[0] = 1;
	For(i,1,18) a[i] = a[i-1] * 10;
	//rep(i,19) cout << a[i] << endl;
	cin >> P >> D;
	P2 = P;
	int k = 19;
	rep(i,19) if (P < a[i]) {

		k = i;break;
	}
	--k;
	ll ans = P;
	For(i,1,k) {
		ll tmp = (P %a[i]) / a[i-1];
		P += a[i-1] * (9-tmp);
		if (P > P2) P -= a[i];
		if (P2-P <= D) ans = P;
	}
	cout << ans << endl;
    
	return 0;
}
