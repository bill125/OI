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

const int inf=~0U>>1, maxa=50000+10;
ll n, m, a, b, t;
ll a1[maxa];
ll ans=0;

int main() {
	setIO("blaster");
	
	cin >>n >> m >> a >> b;
	//n=gi, m=gi, a=gi, b=gi;
	//cout << n * (n-1)/2 << endl;
	a1[1]=(a+b)%m;
	ll p=a1[1]/a+1;
	ans=n*(n-1)/2;
	for (ll i=1;;++i) {
		if (i!=1) a1[i]=a1[i-1]+((m-a1[i-1]-1)/a+1)*a-m;
		ll t=min(n, (m-a1[i]-1)/a+1);

		ll now=0;
		if (i!=1) {
			ans-=(ll)(t)*(t-1)/2*(i-1);
			now+=(ll)(t)*(t-1)/2*(i-1);
		}
		else {
			ans-=(ll)(t)*(t-1)/2;
			now+=(ll)(t)*(t-1)/2;
			
		}

		n-=t;
		For(j,2,i-1) {
			if (a1[i] >= a1[j]) {
				ans-=t;
				now+=t;
			}
		}
		if (i!=1 && p <= t) {
			ans-=(t-p)*(t-p+1)/2;
			now+=(t-p)*(t-p+1)/2;
			
			if (a1[i] >= a1[1]-(p-1)*a) {
				ans -= (t-p+1);
				now += (t-p+1);
			}
		}
		//printf("now=%I64d\n", now);
		//printf("%d\n", i);
		if (n==0) break;
	}
	printf("%lld\n", ans);
	
	return 0;   
}
