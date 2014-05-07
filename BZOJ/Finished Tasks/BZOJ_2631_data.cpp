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

const int inf=~0U>>1, maxn=1000+10;
int n, m;
bool f[maxn][maxn];
bool v[maxn];
queue<int> q;

bool available(int x,int y) {
	fill(v, 0);v[x] = 1;
	while (!q.empty()) q.pop();
	for (q.push(x); !q.empty(); q.pop()) {
		int i=q.front();
		rep(j,n) if (f[i][j] && !v[j]) {
			if (y == j) return 1;
			v[j] = 1;
			q.push(j);
		}
	}
	return 0;
}

int randomv() {
	return rand()%10000 * 10000 + rand()%10000;
}

int main() {
	setIO("test");
	
	srand(time(0));
	
	n=100, m=100;
	printf("%d %d\n", n, m);
	For(i,1,n-1) {
		int j=rand()%i;
		printf("%d %d\n", i+1, j+1);
		f[i][j] = f[j][i] = 1;
	}
	
	rep(i,m) {
		int style;
		for (;;) {
		style=rand()%10;
		int cnt=0, std=100;
		if (style <= 2) {
			int x, y;
			do {
				x=rand()%n, y=rand()%n;
				if (++cnt == std) break;
			} while (x == y || !available(x, y));
			if (cnt == std) continue;
			printf("/ %d %d\n", x+1, y+1);
		}
		else if (style <= 5) {
			int x, y;
			
			do {
				x=rand()%n, y=rand()%n;
			} while (!f[x][y]);
			f[x][y] = f[y][x] = 0;
			printf("- %d %d", x+1, y+1);
			
			
			do {
				x=rand()%n, y=rand()%n;
			} while (x == y || available(x, y));
			printf(" %d %d\n", x+1, y+1);
			f[x][y] = f[y][x] = 1;
		}
		else if (style <= 8) {
			int x=rand()%n, y=rand()%n, c=rand()%10000;
			printf("+ %d %d %d\n", x+1, y+1, c);
		}
		else {
			int x=rand()%n, y=rand()%n, c=rand()%10000;
			printf("* %d %d %d\n", x+1, y+1, c);
		}
		break;
		}
	//	if (i == 0) return 0;
	}
	
	return 0;   
}
