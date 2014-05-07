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
	string in=NAME+".in", out=NAME+".out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, num=70000;
int n, pcnt;
ll MAX=1000000000000000000LL, MOD=20120427;
map<ll, int> id;
ll product[num], dp[2][20][2][num], val[10][20];
int trans[num][10], digit[20];

ll go(bool less, bool first, int pos, bool concern, int pid) {
	if (pid == -1) return 0;
	if (pos>=0) {
		if (less && dp[first][pos][concern][pid]>=0) 
			return dp[first][pos][concern][pid];
		ll result=0;
		
		for (int now=less, d=less ? 9 : digit[pos]; d>=first; --d) {
			result+=go(now, 0, pos-1, concern, trans[pid][d]);
			if (! concern) {
				ll t=go(now, 0, pos-1, 1, trans[pid][d]);
				result += (val[d][pos] * t) % MOD;
			}
			now=1;
			result %= MOD;
		}
		if (less) dp[first][pos][concern][pid]=result;
		return result;
	}
	else return less && (pid == 0 || pid == 2) && concern;
}

void generate() {
	fill(trans, -1);
	product[2]=1;product[0]=product[1]=0;
	ll prime[4]={2, 3, 5, 7};
	int r=3;pcnt=3;
	For(i,2,r-1) rep(j,4) {
		ll k=product[i] * prime[j];
		if (k > MAX || id.count(k)) continue;
		id[k]=pcnt++;
		product[r++]=k;
	}
	
	rep(i,10) trans[0][i]=0;
	trans[1][0]=0;
	id[0]=1, id[1]=2;
	For(i,1,r-1) {
		int t=id[product[i]];
		For(j,1,9) if (product[i] % j==0) trans[t][j]=id[product[i]/j];
	}
}

ll solve(ll A, ll k) {
	if (!id.count(k)) return 0;
	int length=-1;
	for (; A; A/=10) digit[++length]=A%10;
	ll result=0;
	ForD(i,length,0) result += go(i<length, 1, i, 0, id[k]), result %= MOD;
	return result;
}

int main() {
	setIO("test");
	
	generate();

	rep(i,10) {
		val[i][0]=i;
		For(j,1,19) val[i][j]=(val[i][j-1]*10) % MOD;
	}
	
	n=gi;
	fill(dp, -1);
	rep(i,n) {
		ll A=gi, B=gi, k=gi;
		printf("%lld\n", (solve(B+1, k) - solve(A, k) + MOD) % MOD);
	}
	
	return 0;   
}
