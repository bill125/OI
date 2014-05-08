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

const int inf=~0U>>1, maxn=500000+10;
int s[maxn], son[maxn][3];

int main() {
	setIO("neuron");
	
	srand(time(0));
	
	int n=500000;
	printf("%d\n", n);/*
	For(i, 1, n*3) {
		int v, t=min(i, n);
		do {
			v=rand()%t;
		} while (s[v]==3) ;
		son[v][s[v]++] = i+1;
	}
	
	rep(i,n) {
		debug(son[i], 3);
	}*/
	int cnt=2;
	rep(i,n*3) {
		printf("%d%c", cnt++, (i%3==2)?'\n':' ');
		
	}
	
	rep(i,n*2+1) printf("%d%c", (rand()%1000>=300), (i==n*2)?'\n':' ');
	int q=30000;printf("%d\n", q);
	rep(i,q) {
		int p=rand()%(n*2+1)+n+1;
		printf("%d\n", p);
	}
	
	
	return 0;   
}
