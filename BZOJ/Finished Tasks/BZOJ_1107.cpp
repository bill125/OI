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

const int inf=~0U>>2, maxn=100000+10, maxt=1<<18;
int n, m, p, q;
int f[2][maxn], l[2];
vector<Pair> Edge[2];

struct SegTree {
	int h;
	int a[maxt], add[maxt], cov[maxt];
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		fill(a,0), fill(add,0), fill(cov, -1);
	}
	#define y (x<<1)
	#define z (x<<1)+1
	void ref(int x) { a[x]=min(a[y], a[z]); }
	void covIt(int x,int c) { a[x]=min(a[x], c), cov[x]=(cov[x]==-1)?c:min(cov[x], c); }
	void addIt(int x,int c) { add[x]+=c, a[x]+=c; if (cov[x]>=0) cov[x]+=c; }
	void relax(int x) {
		if (add[x]) {
			addIt(y, add[x]), addIt(z, add[x]);
			add[x]=0;
		}
		if (cov[x]!=-1) {
			covIt(y, cov[x]), covIt(z, cov[x]);
			cov[x]=-1;
		}
	}
	void pass(int x) { repD(i,h-1) relax(x>>i+1); }
	void upd(int x) { for (x>>=1; x; x>>=1) ref(x); }
	#undef y
	#undef z
	void cover(int x,int y,int c) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass(l), pass(r);
		while (l+1 < r) {
			if (!(l&1)) covIt(l^1, c);
			if (r&1) covIt(r^1, c);
			l>>=1, r>>=1;
		}
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		upd(l), upd(r);
	}
	void modify(int x,int y,int c) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass(l), pass(r);
		while (l+1 < r) {
			if (!(l&1)) addIt(l^1, c);
			if (r&1) addIt(r^1, c);
			l>>=1, r>>=1;
		}
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		upd(l), upd(r);
	}
	int query(int x,int y) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass(l), pass(r);
		int res=inf;
		while (l+1 < r) {
			if (!(l&1)) res=min(res, a[l^1]);
			if (r&1) res=min(res, a[r^1]);
			l>>=1, r>>=1;
		}
		return res;
	}
}T;

bool cmp(Pair a, Pair b) {
	return a.first > b.first || (a.first == b.first && a.second < b.second) ;
}	

int main() {
	setIO("test");
	
	n=gi, m=gi, p=gi, q=gi; ++m;
	rep(i,p) {
		int a=gi, b=gi+1, v=gi;
		Edge[v].pb(mp(a, b));
	}
	
	l[0]=Edge[0].size(), l[1]=Edge[1].size();
	sort(Edge[0].begin(), Edge[0].end(), cmp);
	sort(Edge[1].begin(), Edge[1].end());
	
	int j;
	For(i,0,q) f[1][i]=n, f[0][i]=1;
	
	j=0;
	T.init(m);
	For(i,2,n) {
		T.modify(1,m,1);
		while (j<l[1] && Edge[1][j].first+1==i) {
			if (j && (Edge[1][j]==Edge[1][j-1])) { ++j; continue; }
			int t=T.query(Edge[1][j].second, m)-1;
			T.cover(1, Edge[1][j].second, t);
			++j;
		}
		int t=T.query(1, m);
		f[0][t]=i;
	}
	For(i,1,q) f[0][i]=max(f[0][i], f[0][i-1]);
	
	j=0; 
	f[1][0]=n;
	T.init(m);
	ForD(i,n-1,1) {
		T.modify(1,m,1);
		while (j<l[0] && Edge[0][j].first==i) {
			if (j && (Edge[0][j]==Edge[0][j-1])) { ++j; continue; }
			int t=T.query(Edge[0][j].second, m)-1;
			T.cover(1, Edge[0][j].second, t);
			++j;
		}
		int t=T.query(1, m);
		f[1][t]=i;
	}
	For(i,1,q) f[1][i]=min(f[1][i], f[1][i-1]);
	
	int ans=0;
	For(i,0,q) ans=max(ans, f[0][i]-f[1][q-i]+1);
	printf("%d\n", ans-max(0, f[0][0]-f[1][0]+1));
	
	return 0;   
}
