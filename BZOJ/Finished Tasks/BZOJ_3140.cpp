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

const int inf=~0U>>1, maxE=10000+10, maxn=5000+10;
int l[3], o[3], ans;
struct Point { 
	int x,y;
	Point(int _x,int _y) : x(_x), y(_y) {}
};
struct Edge {
	int y;
	Edge *next;
	Edge () {}
	Edge (int _y, Edge *_next) : y(_y), next(_next) {}
}mem[maxE], *h[maxn], *C;
bool v[maxn];
int prev[maxn];
vector<Point> q[20];
map<int,int> f[5000];

bool cmp(int a,int b) {
	return l[a]<l[b];
}

void Add_Edge(int x,int y) {
	C->y=y, C->next=h[x], h[x]=C++;
}

bool find(int x) {
	ForE(i,x) {
		int y=i->y;
		if (!v[y]) {
			v[y]=1;
			if (prev[y]==-1 || find(prev[y])) {
				prev[y]=x;
				return 1;
			}
		}
	}
	return 0;
}

void work(int x,int now) {
	if (now>=ans) return;
	if (x==l[0]) {
		
		C=mem;
		rep(i,l[2]) prev[i]=-1;
		rep(i,l[1]) {
			h[i]=0;
			ForV(j,f[i]) Add_Edge(i, j->first);
			rep(j,l[2]) v[j]=0;
			now+=find(i);
		}
		mine(ans,now);
		return ;
	}
	work(x+1,now+1);
	ForV(i,q[x]) {
		if (!f[i->x].count(i->y)) f[i->x][i->y]=1;
		else ++f[i->x][i->y];
	}
	work(x+1,now);
	ForV(i,q[x]) if (--f[i->x][i->y]==0) f[i->x].erase(i->y);
}	

int main() {
	setIO("test");
	
	for (int Td=gi; Td--; ) {
		ans=inf;
		o[0]=0, o[1]=1, o[2]=2;
		l[0]=gi, l[1]=gi, l[2]=gi;
		sort(o,o+3,cmp);
		rep(i,20) q[i].clear();
		
		int t[3];
		for (t[0]=0; t[0]<l[0]; ++t[0]) 
			for (t[1]=0; t[1]<l[1]; ++t[1])
				for (t[2]=0; t[2]<l[2]; ++t[2]) {
					int a=gi;
					if (a==0) continue;
					int x=t[o[0]], y=t[o[1]], z=t[o[2]];
					q[x].pb(Point(y,z));			
				}
		t[0]=l[o[0]], t[1]=l[o[1]], t[2]=l[o[2]];
		l[0]=t[0], l[1]=t[1], l[2]=t[2];
		rep(i,o[1]) f[i].clear();
		
		work(0,0);
		printf("%d\n", ans);
	}
	
	return 0;
}
