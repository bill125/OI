// Author: bill125
// ntr czr
// orz zyx
// using namespace inline

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
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=1000000+10;
int n;
char c[maxn];
int sum[26], maxj[26];
int minSum[26][26], g[26][26];

int main() {
	setIO("test");
	
	n=gi;
	scanf("%s", c);
	
	bool flag=0;
	int len=1, ans=0;
	For(i,1,n-1) {
		if (c[i]!=c[i-1]) {
			flag=1;
			ans=max(ans, len-1);
			len=1;
		}
		else ++len;
	}
	if (!flag) {
		puts("0");return 0;
	}
	else ans=max(ans,len-1);
	
	rep(i,26) rep(j,26) minSum[i][j]=g[i][j]=n+100;
	
	For(i,1,n) {
		int x=c[i-1]-'a';
		sum[x]++;
		rep(y,26) ans=max(ans, sum[x]-sum[y]-minSum[x][y]);
		rep(y,26) minSum[y][x]=min(minSum[y][x], g[y][x]);
		rep(y,26) g[y][x]=min(g[y][x], sum[y]-sum[x]);
	}
	
	printf("%d\n", ans);
	
	return 0;
}
