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

const int inf=~0U>>1, maxn=100000+10, maxl=maxn<<1;
int n;
char c[maxn], s[maxl];
int rad[maxl], f[maxl], num[maxl];

bool cmp(int x,int y) {
	return x - rad[x] < y - rad[y];
}

int find(int x) {
	if (f[x] != x) f[x] = find(f[x]);
	return f[x];
}

int main() {
	setIO("test");
	
	n=gs(c);
	rep(i,n) s[i*2] = '#', s[i*2+1] = c[i];
	n=n*2+1;
	s[n-1] = '#';
	
	rad[0]=0; int k=0;
	For(i,1,n-1) {
		if (k + rad[k] < i) rad[i] = 1;
		else rad[i] = min(rad[k] + k - i, rad[k*2 - i]) + 1;
		while (i - rad[i] >= 0 && i + rad[i] < n && s[i - rad[i]] == s[i + rad[i]]) ++ rad[i];
		-- rad[i];
		if (i + rad[i] > k + rad[k]) k = i;
	}
	
	rep(i,n) f[i] = i, num[i] = i;
	
	sort(num, num + n, cmp);
	
	int ans = 0;
	rep(i, n) {
		int x=num[i];
		int j;
		for (j = find(0); j + rad[j] + 1 < x - rad[x]; f[j] = j+1, j=find(j)) ;
		if (j < x - rad[x]) ans = max(ans, x - j); 
	}
	printf("%d\n", ans);
	
	return 0;   
}
