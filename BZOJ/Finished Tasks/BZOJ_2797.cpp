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

const int inf=~0U>>1, maxm=100000, maxn=300+10;
int n,m,tot=0;
int s[maxm], a[maxn];
int ans[maxn][maxn];
map<int,int> f;

int main() {
	setIO("test");
	
	n=gi, m=n*(n-1)/2;
	rep(i,m) s[i]=gi;
	sort(s, s+m);
	For(i,2,n-1) if (i==2||s[i]!=s[i-1]) {
		if (s[0]+s[1]<=s[i]) break;
		if ((s[0]+s[1]-s[i])&1) continue;
		f.clear();
		rep(j,m) 
			if (!f.count(s[j])) f[s[j]]=1;
			else ++f[s[j]];
		bool flag=1;
		a[0]=(s[0]+s[1]-s[i])>>1;
		For(j,1,n-1) {
			map<int,int>::iterator t=f.begin();
			a[j]=t->first-a[0];
			rep(k,j) {
				int t=a[j]+a[k];
				if (!f.count(t)) { flag=0; break; }
				else if (--f[t]==0) f.erase(t);
			}
			if (!flag) break;
		}
		if (!flag) continue;
		rep(j,n) ans[tot][j]=a[j];
		++tot;
	}
	printf("%d\n", tot);
	rep(i,tot) {
		rep(j,n) printf("%d ", ans[i][j]); 
		puts("");
	}
	
	return 0;
}
