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
#define formap(i,e) for (map<int,int>::const_iterator i = e.begin();i != e.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()
#define v2(i) i->second
#define v1(i) i->first

const int inf = ~0U>>1;

inline void mine(int & a,int b){a=min(a,b);}
inline void maxe(int & a,int b){a=max(a,b);}

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int gI()
{
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

int main()
{
	//setIO("test"); 
	
	int T;
	scanf("%d", &T);
	while (T--) {
		int n,ans = 0;
		int a[1000+10],b[1000+10];
		scanf("%d", &n);
		rep(i,n) a[i] = gi;a[n] = 10000;
		b[0] = a[0];
		For(i,1,n) b[i] = a[i]-a[i-1];
		For(i,0,n-1) if ((n-i)%2==1) ans ^= b[i];
		if (ans == 0) printf("NIE\n");
		else printf("TAK\n");
	}
		
	return 0;
}
