// Author: bill125
// ntr jcpwfloi
// orz LXLWDGY WJMZBMR dilutedream sevenkplus 
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <bitset>

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> Pair;
#define rep(i,n) for (int i=0; i<n; ++i)
#define repD(i,n) for (int i=n-1; i>=0; --i)
#define For(i,a,b) for (int i=a; i<=b; ++i)
#define ForD(i,a,b) for (int i=a; i>=b; --i)
#define ForE(i,a) for (Edge* i=h[a]; i; i=i->next)
#define forv(i,a) for (unsigned int i=0, ___t=a.size(); i<___t; ++i)
#define ForV(i,a) for (__typeof(a.begin()) i = a.begin();i != a.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(a) ((a) & (-(a)))
#define sqr(a) ((a)*(a))
#define pb push_back
#define mp make_pair
#define gi gI()
#define cut puts("===================")
 
void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in=NAME+".in", out=NAME+".out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxm=10000+10, maxn=200+10;
int n, m;
int a[maxm], b[maxm], c[maxm], num[maxn];
vector<int> E[maxn];

bool dfs(int x) {
	For(i,a[x]+1,b[x]-1) ForV(j,E[i]) {
		if (a[*j] < a[x] || b[*j] > b[x]) {
			if (c[*j] == -1) {
				c[*j] = c[x] ^ 1;
				if (!dfs(*j)) return 0;
			}
			else {
				if (c[*j] == c[x] ^ 1) continue;
				return 0;
			}
		}
	}
	return 1;
}

int main() {
	setIO("test");
	
	for (int Td=gi; Td--; ) {
		n=gi, m=gi;
		rep(i,m) a[i]=gi-1, b[i]=gi-1;
	
		int tag=0;
		rep(i,n) {
			int x=gi-1;
			num[x]=tag++;
			E[i].clear();
		}
		rep(i,m) {
			a[i]=num[a[i]], b[i]=num[b[i]];
			if (a[i] > b[i]) swap(a[i],b[i]);
			E[a[i]].pb(i), E[b[i]].pb(i);
			c[i]=-1;
		}
		
		bool flag=1;
		rep(i,m) if (c[i]==-1) {
			c[i]=0;
			if (!dfs(i)) {
				flag=0; break;
			}
		}
		if (flag) puts("YES");
		else puts("NO");
	}
	
	return 0;   
}
