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

const int inf=~0U>>1, maxl=2000;
const ll X=1000000;
int n,m;
struct BigInt {
	ll a[maxl];
	int l;
	BigInt () {fill(a,0);}
	BigInt (ll p) {
		fill(a,0);
		for (l=0;p>0;p/=X) a[l++]=p%X;
	}
	BigInt (char c[]) {
		fill(a,0);
		l=0;
		ll k=1;
		repD(i,strlen(c)) { 
			a[l]+=k*(c[i]-'0');
			if ((k*=10)==X) 
				k=1, ++l;
		}
		if (a[l]>0) ++l;
	}
	bool operator< (const BigInt&A) {
		if (l<A.l) return true;
		if (l>A.l) return false;
		repD(i,l) {
			if (a[i]<A.a[i]) return true;
			if (a[i]>A.a[i]) return false;
		}
		return false;
	}
	bool operator== (const BigInt&A) {
		if (l!=A.l) return false;
		rep(i,l) if (a[i]!=A.a[i]) return false;
		return true;
	}
	BigInt operator+ (const BigInt&A) {
		BigInt t(0LL);
		t.l=max(l,A.l);
		ll k=0;
		rep(i,t.l) {
			k+=a[i]+A.a[i];
			t.a[i]=k%X;
			k/=X;
		}
		while (k) t.a[t.l++]=k%X,k/=X;
		return t;
	}
	BigInt operator*(const ll&A) {
		BigInt t(0LL);t.l=l;
		ll k=0;
		rep(i,l) {
			k+=a[i]*A;
			t.a[i]=k%X;
			k/=X;
		}
		while (k) {
			t.a[t.l++]=k%X;
			k/=X;
		}
		return t;
	}
	void print() {
		if (l==0) {printf("0");return;}
		printf("%lld", a[l-1]);
		repD(i,l-1) {
			for (ll t=a[i]|1;t*10<X;t*=10) printf("0");
			printf("%lld", a[i]);
		}
	}
}ans,ans1,ans2;

int main() {
	//setIO("test");
	
	scanf("%d %d", &n, &m);
	ans1.l=ans1.a[0]=1;
	ans2.l=ans2.a[0]=1;
	
	For(i,2,n) ans1=ans1*i;
	ans1=ans1*(n+1), ans1=ans1*n;
	For(i,n+3-m+1, n+3) ans1=ans1*i;
	
	For(i,1,n+1) ans2=ans2*i;
	For(i,n+2-m+2,n+2) ans2=ans2*i;
	ans2=ans2*2, ans2=ans2*m;
	
	ans=ans1+ans2;
	ans.print();
	
	return 0;
}
