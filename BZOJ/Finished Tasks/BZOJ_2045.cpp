#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define fill(a,b) memset(a,b,sizeof(a))
#define gI gi()

const int inf = ~0U>>1,maxn = 1000000+10;
int A,B,d;
ll f[maxn];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int gi()
{
	char c = getchar();
	while (c != '-' && (c > '9' || c < '0')) c = getchar();
	int n = 0,s = 1;if (c == '-') s = -1,c = getchar();
	while (c >= '0' && c <= '9') n = n*10 + c - '0',c = getchar();
	return n*s;
}
 
int main()
{
	//setIO("test"); 
	
	scanf("%d %d %d", &A, &B, &d);
	if (d > A || d > B) cout << 0 << endl;
	else {
		A/=d,B/=d;
		if (A > B) swap(A,B);
		ForD(i,A,1) 
			if (A/i==1) f[i] = B/i;
			else {
				f[i] = (ll)(A/i)*(B/i);
				For(j,2,A) {
					if (i * j > A) break;
					f[i] -= f[i*j];
				}
			}
		cout << f[1] << endl;
	}
	
	return 0;
}
