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
#include <cmath>

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
int gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1, p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
char gI(int &p) {char c=getchar();while ((c<'0' || c>'9')&&c!='-'&&c!=EOF) c=getchar();ll flag=1;p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9' && c!=EOF) p=p*10+(c-'0'),c=getchar();p*=flag;return c;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n' && c!='\r') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=100000+10, maxm = 500000+10, maxq = 50000+10;
int n, m, q;
int a[maxm], b[maxm];
int num[maxm], ans[maxq];
bool v[maxm];

struct Edge {
	int y;
	Edge *next;
}mem[maxm<<1], *E=mem, *h[maxn];
void Add_Edge(int x,int y) {
	E->next = h[x], h[x] = E, E->y = y, ++E;
}

queue<int> S;

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) a[i]=gi-1, b[i]=gi-1;
	q=gi;
	int anscnt = 0, j;
	rep(i,q) {
		int k; j = 0;
		char c = gI(k);k ^= anscnt;
		while (c != EOF && c != '\r' && c != '\n') {
			c = gI(num[j++]);
			--k;
		}
		if (k != 0) {
			++ anscnt, ans[i-1] = 1;
		}
	}

	fill(v, 0);
	rep(i,j) v[(num[i] ^ anscnt) - 1] = 1;
	rep(i,m) if (!v[i]) Add_Edge(a[i], b[i]), Add_Edge(b[i], a[i]);
	
	rep(i,n) v[i] = 0;
	v[0] = 1;
	for (S.push(0);!S.empty();S.pop()) {
		int x=S.front();
		ForE(e,x) { int y=e->y;
			if (!v[y]) {
				v[y] = 1;
				S.push(y);
			}
		}
	}	
	ans[m-1] = 1;
	rep(i,n) if (!v[i]) { ans[m-1] = 0; break; }
	
	rep(i,q) 
		if (ans[i]) puts("Connected");
		else puts("Disconnected");
	
	return 0;   
}
