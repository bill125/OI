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

const int inf=~0U>>1, N=10000000;
bool v[N+10];
ll miu[N+10], p[N+10];

int main() {
	setIO("test");
	
	For(i,1,N) miu[i]=1;
	For(i,2,N) 
		if (!v[i]) {
			int cnt=0;
			for (int j=i; j<=N ; j+=i) {
				if (++cnt==i) cnt=0, miu[j]=0;
				else miu[j]*=-1;
				v[j]=1;
			}
			v[i]=0;
		}
	For(i,2,N) {
		if (!v[i])  
			for (int j=1; i*j<=N; ++j)
				p[i*j]+=miu[j];
		p[i]+=p[i-1];
	}			
	
	for (int Td=gi; Td--; ) {
		ll n=gi, m=gi;
		ll ans=0;
		if (n>m) swap(n, m);
		for (int t=1; t<=n; ++t) {
			int x=min(n/(n/t), m/(m/t));
			ans+=(n/t)*(m/t)*(p[x]-p[t-1]);
			t=x;
		}
		printf("%lld\n", ans);
	}	
	
	return 0;
}
