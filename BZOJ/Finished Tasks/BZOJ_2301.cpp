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

const int inf=~0U>>1, maxn=50000+10;
int p[maxn], N=50000;
bool v[maxn];

int ask(int a,int b) {
	int ans=0;
	if (a>b) swap(a,b);
	if (a<=0) return 0;
	for (int t=1; t<=a; ++t) {
		int m=min(a/(a/t), b/(b/t));
		ans+=(p[m]-p[t-1])*(a/t)*(b/t);
		t=m;
	}
	return ans;
}

int main() {
	setIO("test");
	
	For(i,1,N) p[i]=1;
	fill(v,0);
	For(i,2,N) {
		if (!v[i]) {
			for (int j=1;i*j<=N;++j) {
				if (j%i) p[i*j]*=-1;
				else p[i*j]=0;
				v[i*j]=1;
			}
		}
		p[i]+=p[i-1];
	}	
	
	for (int Td=gi; Td--; )  {
		int a=gi-1, b=gi, c=gi-1, d=gi, k=gi;
		a/=k, b/=k, c/=k, d/=k;

		int ans=ask(b,d)-ask(b,c)-ask(a,d)+ask(a,c);
		printf("%d\n", ans);
	}
	
	return 0;
}
