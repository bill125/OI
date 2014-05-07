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

const int inf=~0U>>1, maxn=40000+10;
int n,m;
int tag[maxn];
struct Edge {
	int y;
	Edge *next;
	Edge (int _y, Edge *_next) : y(_y), next(_next) {}
}*h[maxn];

void Add_Edge(int x,int y) {
	h[x]=new Edge(y, h[x]);
	h[y]=new Edge(x, h[y]);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) {
		int a=gi-1, b=gi-1;
		Add_Edge(a, b);
	}
	
	fill(tag,0);
	tag[0]=tag[1]=-1;
	int cntA=0, cntB=0, ans=0;

	ForE(i,0) tag[i->y]=1, ++cntA;
	ForE(i,1) tag[i->y]=2, ++cntB;
	ans+=cntA*(cntA-1)/2;
	ans+=cntB*(cntB-1)/2;
	ans+=cntA+cntB;
	ans+=(n-2-cntA-cntB)*(n-2-cntA-cntB-1)/2;
	//printf("%d\n", ans);
	
	rep(i,n) {
		if (tag[i]==1) 
			ForE(e,i) if (tag[e->y]==0) 
				tag[e->y]=3, ans+=cntA;
		if (tag[i]==2)
			ForE(e,i) if (tag[e->y]==0) 
				tag[e->y]=4, ans+=cntB;
	}
	
	rep(i,n) if (tag[i]==0) 
		ans+=max(cntA, cntB);
	printf("%d\n", ans-m);
	
	
	
	return 0;
}
