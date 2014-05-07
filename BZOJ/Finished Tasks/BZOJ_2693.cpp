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

const int inf=~0U>>1, N=10000000, maxn=N+10, MOD=1e8+9;
int tot=0;
ll miu[maxn], p[maxn], M[maxn];
int  pr[maxn];
bool v[maxn];

void inc(ll &a, ll b) {
	a+=b;
	if (a>=MOD) a-=MOD;
}

int main() {
	setIO("test");
	
	For(i,1,N) miu[i]=1;
	p[1]=1;
	For(i,2,N) {
		if (!v[i]) {
			pr[tot++]=i;
			miu[i]=-1;
			p[i]=p[1]+miu[i]*i;
			M[i]=i;
		}
		rep(j,tot) {
			if (pr[j]*i>N) break;
			v[pr[j]*i]=1;
			if (i%pr[j]==0) { 
				miu[pr[j]*i]=0, M[pr[j]*i]=M[i]*pr[j];
				p[pr[j]*i]=p[i/M[i]]*(p[M[i]]+(M[i]*pr[j]*miu[M[i]*pr[j]])%MOD)%MOD; 
				break; 
			}
			else miu[pr[j]*i]=-miu[i], M[pr[j]*i]=pr[j], p[pr[j]*i]=(p[i]*p[pr[j]])%MOD;;
		}
	}
	For(i,2,N) {
		p[i]*=i, p[i]%=MOD;
		inc(p[i], p[i-1]);
		p[i]=(p[i]%MOD+MOD)%MOD;
	}
	
	for (int Td=gi; Td--; ) {
		ll n=gi, m=gi, ans=0;
		if (n>=m) swap(n,m);
		for (ll i=1; i<=n; ++i) {
			ll t=min(n/(n/i), m/(m/i));
			ll t1=((n/i)*(n/i+1)/2)%MOD;
			ll t2=((m/i)*(m/i+1)/2)%MOD;
			ll t3=p[t]-p[i-1];
			if (t3<0) t3+=MOD;
			inc(ans, ((t1*t2)%MOD*t3)%MOD);
			i=t;
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
