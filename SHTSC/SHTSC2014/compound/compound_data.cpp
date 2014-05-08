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
	string in=NAME+".in";freopen(in.c_str(),"w",stdout);
	#endif
}
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=5000+10;
int n, m ,q;
bool f[maxn][maxn];
int p[maxn];
bool v[maxn];

bool check(int x,int y) {
	queue<int> s;
	fill(v, 0);v[x]=1;
	for (s.push(x); !s.empty(); s.pop()) {
		int x=s.front();
		rep(y,n) if (f[x][y] && !v[y]) {
			s.push(y);
			v[y]=1;
		}
		//printf("%d ", x);
	}
	//puts("");
	if (!v[y]) return 1;
	//printf("#%d %d\n", 1+x, 1+y);
	rep(i,n) if (f[x][i] && f[y][i]) return 1;
	return 0;
}

int main() {
	setIO("compound");
	
	srand(time(0));
	
	n=6, m=7, q=100;
	printf("%d %d\n", n, m);
	rep(i,m) {
		int x, y;
		do {
			x=rand()%n, y=rand()%n;
		} while (x==y || f[x][y] || !check(x, y));
		f[x][y]=f[y][x]=1;
		printf("%d %d\n", x+1, y+1);
	}
	printf("%d\n", q);
	rep(i,q) {
		int style=rand()%5;
		if (style == 0) { puts("Q"); continue; }
		int x,y;
		do {
			x=rand()%n, y=rand()%n;
		} while (x==y || (!f[x][y] && !check(x, y)));
		if (f[x][y]) {
			printf("D %d %d\n", x+1, y+1);
			f[x][y]=f[y][x]=0;
		}
		else {
			printf("A %d %d\n", x+1, y+1);
			f[x][y]=f[y][x]=1;
		}
	}
	
	return 0;   
}
