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

const int inf=~0U>>1,maxn=100000+10,maxdep=20;
int n,s;
db ans;
db A[maxn],B[maxn],R[maxn],f[maxn],k[maxn],b[maxn];
int num1[maxn], num2[maxdep][maxn], t[maxn];

bool cmp1(int x,int y) { return k[x]<k[y] || (k[x]==k[y] && b[x]>b[y]); }
bool cmp2(int x,int y) { return A[x]/B[x]<A[y]/B[y]; }

db slope(int x,int y) {
	return (b[x]-b[y])/(k[y]-k[x]);
}

void mgsort(int l,int r,int dep) {
	if (l==r) {
		num2[dep][l]=l;
		return ;
	}
	int m=(l+r)>>1;
	mgsort(l,m,dep+1), mgsort(m+1,r,dep+1);
	int i=l, j=m+1, qr=l;
	while (i<=m || j<=r) 
		if ((i<=m) && (j==r+1 || cmp2(num2[dep+1][i], num2[dep+1][j]))) num2[dep][qr++]=num2[dep+1][i++];
		else num2[dep][qr++]=num2[dep+1][j++];
}

void work(int l,int r,int dep) {
	if (l==r) {
		maxe(f[l],ans);
		maxe(ans,f[l]);
		b[l]=f[l]/(A[l]*R[l]+B[l]);
		k[l]=b[l]*R[l];
		return ;
	}
	int m=(l+r)>>1;
	work(l,m,dep+1);
	
	int ql=0,qr=-1;
	For(_i,l,m) {
		int i=num1[_i];
		if (_i==l || k[i]!=k[num1[_i-1]]) {
			while (ql<qr && slope(t[qr-1],t[qr])>=slope(t[qr],i)) --qr;
			t[++qr]=i;
		}
	}
	
	For(_i,m+1,r) {
		int i=num2[dep+1][_i];
		while (ql<qr && slope(t[ql],t[ql+1])<=A[i]/B[i]) ++ql;
		int j=t[ql];
		f[i]=max(f[i],k[j]*A[i]+b[j]*B[i]);
		
	}
		
	work(m+1,r,dep+1);
	
	int i=l, j=m+1; qr=l;
	while (i<=m || j<=r) 
		if ((i<=m) && (j==r+1 || cmp1(num1[i], num1[j]))) t[qr++]=num1[i++];
		else t[qr++]=num1[j++];
	For(i,l,r) num1[i]=t[i];
}

int main() {
	setIO("test");
	
	n=gi, ans=gi;
	For(i,1,n) scanf("%lf %lf %lf", &A[i], &B[i], &R[i]), num1[i]=i;
	
	mgsort(1,n,0);
	work(1,n,0);
	
	printf("%.3f\n", ans);
	
	return 0;
}
