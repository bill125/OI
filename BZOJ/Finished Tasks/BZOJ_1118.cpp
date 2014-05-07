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

const int inf = ~0U>>1,maxnum = 100+10,maxn = 100000+10;
int n,m,T;
int a[maxn],b[maxn],c1[maxnum],c2[maxnum];
map<int,bool> s[maxn];

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

bool work(int l,int r,int p,int q)
{
	int id = p*100000+q;
	if (s[l][r%11].find(id) != s[l][r%11].end()) return s[l][r%11][id];
	bool & f = s[l][r%11][id]; f = true;
	if (l == r && p == q) return f;
	
	//if (l != 0) {
		//printf("%d\n", l);

	
	int x,y;
	For(i,l,r) if (--c1[a[i]] == 0) {x = i; break;}
	For(i,p,q) if (--c2[b[i]] == 0) {y = i; break;}
	if (a[x] != b[y] || !work(x+1,r,y+1,q)) return f = false;
	For(i,l,x) ++c1[a[i]];
	For(i,p,y) ++c2[b[i]];
	
	ForD(i,r,l) if (--c1[a[i]] == 0) {x = i; break;}
	ForD(i,q,p) if (--c2[b[i]] == 0) {y = i; break;}
	if (a[x] != b[y] || !work(l,x-1,p,y-1)) return f = false;
	For(i,x,r) ++c1[a[i]];
	For(i,y,q) ++c2[b[i]];
	
	return f;
}

int main()
{
	//setIO("test"); 
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		rep(i,n) {
			a[i] = gi-1;
			if (i && a[i] == a[i-1]) --i,--n;
		}
		rep(i,m) {
			b[i] = gi-1;
			if (i && b[i] == b[i-1]) --i,--m;
		}
		fill(c1,0),fill(c2,0);
		rep(i,n) ++c1[a[i]];
		rep(i,m) ++c2[b[i]];
		bool flag = true;
		rep(i,100) if (!c1[i] != !c2[i]) {flag = false; break;}
		rep(i,n) rep(j,11) s[i][j].clear();
		if (flag && work(0,n-1,0,m-1)) printf("1\n");
		else printf("0\n");
	}
		
	return 0;
}
