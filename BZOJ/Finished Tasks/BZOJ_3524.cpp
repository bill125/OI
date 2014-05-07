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
char c[100];
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}
inline void pI(int k) {
	if (!k) { putchar('0');putchar('\n'); return; }
	int r=0;
	while (k) {
		c[r++]=(k%10 + '0');
		k/=10;
	}
	repD(i,r) putchar(c[i]);
	putchar('\n');
}

const int inf=~0U>>1, maxn=500000+50;
int n, m;
int cnt[maxn][20], lab[maxn], sum[maxn];
Pair a[maxn];

inline int find(int k,int p) {
    int l=lab[k] - 1, r=lab[k] + sum[k];
    while (l+1 < r) {
        int m=l+r>>1;
        if (a[m].second >= p) r=m;
        else l=m;
    }
    return r;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	For(i,1,n) {
		a[i].first=gi, a[i].second=i;
		rep(j,20) cnt[i][j] = cnt[i-1][j] + ((a[i].first & (1 << j)) > 0);
	}
	
	sort(a+1, a+n+1);
	For(i,1,n) lab[i]=-1;
	For(i,1,n) {
		if (lab[a[i].first] == -1) lab[a[i].first] = i;
		++sum[a[i].first];
	}
	
	rep(i,m) {
		int l=gi, r=gi, d=r-l+1 >> 1;
		int k=0;
		rep(j,20) if (cnt[r][j] - cnt[l-1][j] > d)
			k |= 1 << j;
		int ans = (lab[k] != -1 && find(k, r+1) - find(k, l) > d) ? k : 0;
		pI(ans);
	}
	
	return 0;   
}
