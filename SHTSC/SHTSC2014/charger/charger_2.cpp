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
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=500000+10;
int n;
int p[maxn];
int a[maxn], b[maxn];
db c[maxn], r[maxn], ans=0;
bool light[maxn];
queue<int> q;
db all=0;
struct Edge {
	int y; db c;
	Edge *next;
	Edge () {}
}*h[maxn], *e, mem[maxn<<1];

Edge *makeedge(int a,int b, db c) {
	e->y=b;
	e->next=h[a];
	h[a]=e;
	e->c=c;
	return e++;
}

void Add_Edge(int a,int b, db c){
	h[a]=makeedge(a, b, c);
}

void fuckvertex(db gl) {
	while (!q.empty()) q.pop();

	rep(M,(1<<n)) {
		db cnt=0, gl2=1;
		fill(light, 0);
		rep(i,n) if ((1<<i)&M) {
			q.push(i);
			light[i]=1;
			gl2*=r[i];
			//printf(" %d ", i);
		}
		else gl2*=1-r[i];
		
		for (;!q.empty();q.pop()) {
			int x=q.front();++cnt;
			ForE(e,x) {
				int y=e->y;
				if (!light[y]) q.push(y), light[y]=1;
			}
		}
		//printf(":%.0f\n", cnt);
		if (light[0]) ++all;
		ans+=cnt *gl *gl2;
	}
}

void fuckedge() {
	rep(M,(1<<(n-1))) {
		fill(h, 0);
		db gl=1;
		e=mem;
		rep(j,n-1) if ((1<<j) & M) {
			gl*=c[j];
			Add_Edge(a[j], b[j], c[j]);
			Add_Edge(b[j], a[j], c[j]);
			//printf("%d %d\n", a[j], b[j]);
		}
		else gl*=1-c[j];
		fuckvertex(gl);
		//cut;
	}
}

int main() {
	setIO("charger");
	
	n=gi;
	rep(i,n-1) {
		a[i]=gi-1, b[i]=gi-1, c[i]=gi;
		c[i]/=100;
	}
	rep(i,n) r[i]=gi, r[i]/=100;
	
	fuckedge();
	
	printf("%.6f\n", ans);	
	
	return 0;   
}
