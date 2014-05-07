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

const int inf=~0U>>1, maxn=100000+10, maxm=maxn;
int n, m;
int a[maxn], w[maxm], b[maxm];
int v[maxn], num[maxn];

bool ok(int l) {
	memcpy(b, w, sizeof(b));
	repD(i,l) {
		rep(j,m) {
			int k=min(b[j]/v[i], num[i]);
			b[j]-=k*v[i];
			if ((num[i]-=k)==0) break;
		}
		if (num[i]) return 0;
	}
	return 1;
}

int main() {
	setIO("test");
	
	m=gi, n=gi;
	rep(i,m) w[i]=gi;
	rep(i,n) a[i+1]=gi;
	sort(a+1, a+n+1);a[0]=-1;
	
	int l=0, r=n+1;
	while (l+1 < r) {
		int m=(l+r)>>1;
		int cnt=0;
		For(i,1,m) 
			if (a[i]==a[i-1]) ++num[cnt-1];
			else v[cnt]=a[i], num[cnt]=1, ++cnt;
		if (ok(cnt)) l=m;
		else r=m;
	}
	printf("%d\n", l);
	
	return 0;   
}
