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

const int inf=~0U>>1, maxn = 10000+10, limits = 100;
int n;
db a, b, vmax, f;
db s[maxn], k[maxn], sv[maxn], v[maxn];

db check(db lambda) {
	db sum = 0, v_ = sqrt(-1. / lambda / a);
	rep(i, n) {
		v[i] = v_ - sv[i];
		if (a * (sv[i] + v[i]) + b * k[i] > 0) sum += s[i] * (a * (sv[i] + v[i]) + b * k[i]);
	}
	return sum;
}

int main() {
	setIO("test");
	
	for (int Td = gi; Td--; ) {
		scanf("%lf %lf %lf %lf", &a, &b, &vmax, &f);
		n = gi;
		rep(i,n) {
			db x, y;
			scanf("%lf %lf", &x, &y);
			x /= 1000., y /= 1000.;
			s[i] = sqrt(x * x + y * y);
			k[i] = y / x;
			if (k[i] < 0) sv[i] = -k[i] * b / a;
			else sv[i] = 0;
		}
		
		db l = -1000000000., r = 0;
		for (int cnt = 0; cnt < limits; ++cnt) {
			db m = (l + r)/2;
			if (check(m) <= f) l = m;
			else r = m;
		}
		
		if (check(l) > f) {
			puts("IMPOSSIBLE");
			continue;
		}
		
		rep(i,n) v[i] = max(v[i], (db)0), v[i] += sv[i], v[i] = min(v[i], vmax);
		db time = 0;
		rep(i, n) time += s[i] / v[i];
		printf("%.5f\n", time);
	}
	
	return 0;   
}
