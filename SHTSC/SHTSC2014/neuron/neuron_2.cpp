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
	string in=NAME+".in", out=NAME+"2.out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxp=1500000+10, maxn=500000+10, maxe=2000000+10;
int n;
int p[maxp], x[maxn][3], q[maxp];
int s[maxp];

struct Edge {
	int y;
	Edge *next;
}*h[maxn], mem[maxe], *e=mem;
Edge*makeedge(int x,int y) {
	e->y=y, e->next=h[x];
	return e++;
}
void Add_Edge(int x,int y) {
	h[x]=makeedge(x, y);
}

void ref(int t) {
	int tmp=0;
	rep(i,3) {
		tmp+=s[x[t][i]];
		
	}
	s[t]=tmp>=2;
}

void upd(int t) {
	for (t=p[t]; t!=-1; t=p[t]) ref(t);
}

int main() {
	setIO("neuron");
	
	n=gi;
	rep(i,n) 
		rep(j,3) {
			x[i][j]=gi-1;
			p[x[i][j]]=i;
			Add_Edge(i, x[i][j]);
		}
	
	int r=1;q[0]=0;
	rep(i,r) {
		int x=q[i];
		ForE(e, x) {
			int y=e->y;
			if (y>=n) continue;
			q[r++]=y;
		}
	}
	//debug(q, r);
	
	p[0]=-1;
	For(i,n,3*n) s[i]=gi;
	repD(i,n) ref(q[i]);
	//debug(s, r);
	
	for (int q=gi; q--; ) {
		int x=gi-1;
		s[x]^=1;
		upd(x);ref(0);
		printf("%d\n", s[0]);
	}
	
	
	return 0;   
}
