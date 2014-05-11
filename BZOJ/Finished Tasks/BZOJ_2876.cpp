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

const int inf=~0U>>1, maxn = 10000+10;
const db eps = 0.00000000000001;
int n;
db E, s[maxn], k[maxn], v[maxn], x[maxn];

inline db sqr(db x) { return x * x; }
inline db cube(db x) { return x * x * x; }

db calc(int i,db lambda) {
	db l = v[i], r = 10000, std = -1. /2. / lambda/ k[i];
	while (l + eps < r) {
		db m = (l + r) / 2;
		if ( cube (m) - v[i] * sqr(m) <= std) l = m;
		else r = m;	
	}
	return l;
}

db check(db lambda) {
	rep(i,n) x[i] = calc(i, lambda);
	db E = 0;
	rep(i,n) E += k[i] * sqr(x[i] - v[i]) * s[i];
	return E;
}

int main() {
	setIO("test");
	
	n=gi;
	scanf("%lf", &E);
	rep(i,n) scanf("%lf %lf %lf", &s[i], &k[i], &v[i]);
	
	db l = -100, r = 0;
	while (l + eps < r) {
		db m = (l + r) / 2;
		if (check(m) > E) r = m;
		else l = m;
	}
	
	check(l);
	
	db time = 0;
	rep(i,n) time += s[i] / x[i];
	printf("%.8f\n", time);
	
	return 0;   
}
