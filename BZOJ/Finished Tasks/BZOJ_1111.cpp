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

const int inf=~0U>>1, maxn=3000+10;
int n,MOD=1000000000;
int a[maxn], b[maxn];
int f[maxn][2], g[maxn][2];
char c[maxn];

inline void upd(int &a,int b) {
	if ((a+=b)>=MOD) a-=MOD;
}

int main() {
	setIO("test");
	
	scanf("%s", c);
	n=strlen(c);
	rep(i,n) a[n-i-1]=c[i]-'0';
	
	int l=0;
	while (n) {
		int k=0;
		repD(i,n) {
			k=k*10+a[i];
			a[i]=k/4;
			k%=4;
		}
		b[l++]=k;
		while (n && a[n-1] == 0) --n;
	}

	f[l][0]=0, f[l][1]=1;
	g[l][0]=g[l][1]=1;
	repD(i,l) rep(j,2) {
		f[i][j]=inf;g[i][j]=0;
		rep(k,2) {
			int t=f[i+1][k]+abs(b[i]+j-k*4);
			if (t<f[i][j]) {
				f[i][j]=t;
				g[i][j]=g[i+1][k];
			}
			else if (t==f[i][j]) 
				upd(g[i][j], g[i+1][k]);
		}	
	}
	printf("%d\n", g[0][0]);
	
	return 0;   
}
