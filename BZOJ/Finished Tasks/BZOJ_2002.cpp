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
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn=200000+10;
int n, m;
int a[maxn], r[maxn], pos[maxn], step[maxn];

void modify(int i,int k) {
	a[i]=k;
	ForD(j,i,1) {
		if (r[j] != r[i]) return ;
		if (j+a[j] > r[i]) {
			pos[j] = j+a[j];
			step[j] = 1;
		}
		else {
			pos[j] = pos[j+a[j]];
			step[j] = step[j+a[j]] + 1; 
		}
	}
}

int query(int i) {
	int ans;
	for (ans=0; i<=n; i=pos[i]) ans+=step[i];
	return ans;
}

void prework() {
	int k=(int)sqrt((db)n);
	int nowr=k;
	For(i,1,n) {
		r[i]=nowr;
		if (nowr==i) nowr=min(nowr+k, n);
	}
	For(i,1,n) for (step[i]=0, pos[i]=i; pos[i]<=r[i]; pos[i]+=a[pos[i]]) ++step[i]; 
}

int main() {
	setIO("test");
	
	n=gi;
	For(i,1,n) a[i]=gi;
	prework();
	
	//For(i,1,n) if (pos[i]<=i) printf("%d %d\n", i, pos[i]);
	
	for (int m=gi; m--; ) {
		int style=gi;
		if (style==1) {
			int x=gi+1;
			printf("%d\n", query(x));
		}
		else {
			int x=gi+1, k=gi;
			modify(x, k);
		}		
	}
	
	return 0;   
}
