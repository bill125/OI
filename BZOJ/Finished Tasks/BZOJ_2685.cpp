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
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1, maxn=100+3;
int n;
db f[maxn][maxn][maxn], g[maxn][maxn], P[maxn][maxn];
db s[maxn];

int main() {
	setIO("test");
	
	n=gi;
	
	For(i,1,n) {
		P[i][0]=1;
		For(j,1,i) P[i][j]=P[i][j-1]*(i-j+1);
	}

	fill(f,0), fill(g,0);
	f[0][0][0]=1, g[0][0]=1;
	rep(i,n+1) g[0][i]=1;
	For(i,2,n) {
		For(j,2,i) {
			f[i][j][1]=(db)g[i-j][j-1]*P[n-i+j][j]/j;
			For(k,2,i/j) f[i][j][k]=(db)f[i-j][j][k-1]*P[n-i+j][j]/j/k;
		}
		For(j,2,n) {
			g[i][j]=g[i][j-1];
			For(k,1,i/j) g[i][j]+=f[i][j][k];
		}
	}
	db a=0;
	For(j,2,n) For(k,1,n/j+1) a+=f[n][j][k]*j*k;
	s[1]=0, s[2]=1;
	For(i,3,n) s[i]=(i-1)*(s[i-1]+s[i-2]);
	printf("%.9f\n", a/s[n]);
	
	return 0;
}
