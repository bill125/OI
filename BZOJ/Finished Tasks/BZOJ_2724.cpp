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
#include <cmath>

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

const int inf=~0U>>1, maxn=40000+10, maxs=200+10;
int n, m;
int a[maxn], next[maxn], num[maxn], cnt[maxn], lab[maxn];
int zs[maxs][maxn];
map<int, int> f;
vector<int> pos[maxn];

inline int find(int k, int p) {
	int l=-1, r=pos[k].size();
	while (l+1 < r) {
		int m=l+r>>1;
		if (pos[k][m] >= p) r=m;
		else l=m;
	}
	return r;
}

inline int calc(int s,int l,int r) {
	return find(s, r+1) - find(s, l);
}

int main() {
	setIO("test");
	
	int tag=0;
	n=gi, m=gi;
	int d=(int) sqrt((db) n);
	rep(i,n) a[i]=gi, f[a[i]]=1;
	ForV(i, f) num[tag]=i->first, i->second=tag++;
	rep(i,n) a[i]=f[a[i]], pos[a[i]].pb(i);
	
	int s=1; lab[0]=0;
	for ( ;lab[s-1]<n-1; ++s) lab[s]=min(n-1, lab[s-1]+d);
	
	int j=s-1;
	repD(i,n) {
		if (j && lab[j-1] == i) --j;
		next[i]=j;
	}
	rep(i,s) {
		rep(j,tag) cnt[j]=0;
		int maxcnt=-1;
		For(j,lab[i],n-1) {
			++cnt[a[j]];
			if (cnt[a[j]] > maxcnt || cnt[a[j]] == maxcnt && a[j] < zs[i][j-1]) {
				maxcnt=cnt[a[j]];
				zs[i][j]=a[j];
			}
			else zs[i][j]=zs[i][j-1];
		}
	}
	
	int ans=0;
	rep(i,m) {
		int l = (gi + ans - 1) % n, r = (gi + ans - 1) % n;
		if (l > r) swap(l, r);
		
		int p=next[l], maxcnt=-1;
		if (lab[p] <= r) maxcnt=calc(zs[p][r], l, r), ans=zs[p][r];
		int t=min(lab[p]-1, r);
		For(j,l,t) {
			int t=calc(a[j], l, r);
			if (t > maxcnt || t==maxcnt && a[j] < ans) maxcnt=t, ans=a[j];
		}
		ans=num[ans];
		printf("%d\n", ans);
	}
	
	return 0;   
}
