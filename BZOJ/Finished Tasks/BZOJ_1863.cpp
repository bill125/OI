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

const int inf=~0U>>1, maxn=20000+10;
int n;
int a[maxn], l[maxn], r[maxn];

bool ok(int m) {
	l[0]=r[0]=a[0];
	For(i,1,n-1) {
		r[i]=min(a[i], a[0] - l[i-1]);
		l[i]=max(0, a[0] + a[i] + a[i-1] - r[i-1] - m); 
	}
	return l[n-1]==0;
}

int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) a[i]=gi;
	
	if (n==1) { printf("%d\n", a[0]); return 0; }
	
	int ans=a[0]+a[n-1];
	rep(i,n-1) ans=max(ans, a[i]+a[i+1]);
	
	if (!(n&1)) { printf("%d\n", ans); return 0; }
	
	int l=ans-1, r=1+(ans<<1);
	while (l+1 < r) {
		int m=l+r>>1;
		if (ok(m)) r=m;
		else l=m;
	}
	printf("%d\n", r);
	
	return 0;   
}
