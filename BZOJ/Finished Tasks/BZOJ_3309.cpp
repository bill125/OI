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

const int inf=~0U>>1,N=10000000, maxn=N+10;
int tot=0;
int pr[maxn], Mpr[maxn], Mq[maxn], Cut[maxn];
int g[maxn];
bool v[maxn];

int main() {
	setIO("test");
	
	Cut[1]=1;
	For(i,2,N) {
		if (!v[i]) {
			pr[tot++]=i;
			Mq[i]=1, Mpr[i]=i, g[i]=1, Cut[i]=1;
		}
		else {
			if (Mq[Cut[i]]==Mq[i]) g[i]=-g[Cut[i]];
			else if (Cut[i]>1) g[i]=0;
			else g[i]=1;
		}
		rep(j,tot) {
			if (i*pr[j]>N) break;
			v[i*pr[j]]=1;
			
			Mpr[i*pr[j]]=pr[j];
			if (i%pr[j]) Mq[i*pr[j]]=1, Cut[i*pr[j]]=i;
			else {
				Mq[i*pr[j]]=Mq[i]+1, Cut[i*pr[j]]=Cut[i];
				break;
			}
		}
	}
	For(i,2,N) g[i]+=g[i-1];
	
	for (int Td=gi; Td--; ) {
		ll a=gi, b=gi, ans=0;;
		if (a>b) swap(a,b);
		for (ll i=1; i<=a; ++i) {
			ll t=min(a/(a/i), b/(b/i));
			ans+=(g[t]-g[i-1])*(a/i)*(b/i);
			i=t;
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
