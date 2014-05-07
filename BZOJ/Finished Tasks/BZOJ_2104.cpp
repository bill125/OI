//Author: bill125

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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define pb push_back
#define mp make_pair
#define v1 first
#define v2 second
#define gi gI()
#define cut puts("===================")

void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in = NAME + ".in";
	string out = NAME + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
	#endif
}
int gI() {
	char c=getchar();
	while ((c<'0' || c>'9')&&c!='-') c=getchar();
	int flag=1,p=0;
	if (c=='-') flag=-1,c=getchar();
	while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();
	return p*flag;
}
int gs(char *C) {
	char c=getchar();
	while (c==' ' || c=='\n') c=getchar();
	int l=0;
	while (c!=' ' && c!='\n') C[l++]=c,c=getchar();
	C[l]=0;
	return l;
}

template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i], (i==n-1) ? '\n' : ' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1,maxm=100000+10,n=6;
int m;
int w[n][maxm];

struct SegTree {
	SegTree () {}
	SegTree (int ,int ) ;
	SegTree *ls, *rs;
	int l,r;
	int ll[n][n], rr[n][n], mm[n][n], lr[n][n];
	bool upd() ;
	bool chg(int) ;
	void set() ;
	void upd_left(int dl[], int dr[]) {
		int d[n];
		int m=(l+r)>>1;
		rep(i,n) {
			d[i]=inf;
			rep(j,n) mine(d[i],dr[j]+mm[i][j]);
		}
		rep(i,n) {
			dr[i]=inf;
			rep(j,n) {
				mine(dl[i],ls->lr[i][j]+d[j]);
				mine(dr[i],rs->lr[j][i]+d[j]-w[j][m]);
				
			}
		}
	}
	void upd_right(int dl[], int dr[]) {
		int d[n];
		int m=(l+r)>>1;
		rep(i,n) {
			d[i]=inf;
			rep(j,n) mine(d[i],dl[j]+mm[j][i]-w[j][m]);
		}
		rep(i,n) {
			dl[i]=inf;
			rep(j,n) {
				mine(dl[i],d[j]+ls->lr[i][j]);
				mine(dr[i],d[j]+rs->lr[j][i]-w[j][m]);
			}
		}
	}
	void ask2(int x,int y,int dl[],int dr[]) {
		if (l+1==r) {
			rep(i,n) dl[i]=dr[i]=mm[x][i];
			return;
		}
		int m=(l+r)>>1;
		if (m<=y) {
			rs->ask2(x,y,dl,dr);
			upd_right(dl,dr);
		}
		else {
			ls->ask2(x,y,dl,dr);
			upd_left(dl,dr);
		}
	}
	int ask(int x1,int y1,int x2,int y2, int dl1[], int dr1[], int dl2[], int dr2[]) {
		if (l+1==r) {
			rep(i,n) {
				dl1[i]=dl2[i]=mm[x1][i];
				dr1[i]=dr2[i]=mm[x2][i];
			}
			return mm[x1][x2];
		}
		int m=(l+r)>>1,res;
		if (y2<m) {
			res=ls->ask(x1,y1,x2,y2,dl1,dr1,dl2,dr2);
			rep(i,n) rep(j,n) 
				res=min(res,dl2[i]+mm[i][j]+dr2[j]);
			upd_left(dl1,dl2);
			upd_left(dr1,dr2);
		}
		else if (m<=y1) {
			res=rs->ask(x1,y1,x2,y2,dl1,dr1,dl2,dr2);
			rep(i,n) rep(j,n)
				res=min(res,dr1[i]+mm[i][j]+dl1[j]-w[i][m]-w[j][m]);
			upd_right(dl1,dl2);
			upd_right(dr1,dr2); 
		}
		else {
			ls->ask2(x1,y1,dl1,dl2);
			rs->ask2(x2,y2,dr1,dr2);
			res=inf;
			rep(i,n) rep(j,n) 
				res=min(res,dl2[i]+mm[i][j]+dr1[j]-w[j][m]);
			upd_left(dl1,dl2);
			upd_right(dr1,dr2);
		}
		return res;
	}
}Tnull,*null=&Tnull,*root;
SegTree::SegTree(int _l,int _r) {
	l=_l, r=_r;
	if (l+1!=r) {
		int m=(l+r)>>1;
		ls=new SegTree(l,m);
		rs=new SegTree(m,r);
		rep(i,n) rep(j,n) ll[i][j]=rr[i][j]=lr[i][j]=mm[i][j]=1000000000;
		upd();
	}
	else {
		ls=rs=null;
		set();
	}
}
bool SegTree::upd() {
	bool updated=0;
	int d1[n][n], d2[n];
	int m=(l+r)>>1;
	
	rep(i,n) rep(j,n) d1[i][j]=min(ls->rr[i][j]+w[i][m]+w[j][m],rs->ll[i][j]);
	rep(k,n) rep(i,n) rep(j,n) mine(d1[i][j],d1[i][k]+d1[k][j]-w[k][m]);
	rep(i,n) rep(j,n) 
		if (d1[i][j]!=mm[i][j]) 
			mm[i][j]=d1[i][j], updated=1;
			
	rep(i,n) {
		rep(j,n) {
			d2[j]=inf;
			rep(k,n) mine(d2[j],ls->lr[i][k]+d1[k][j]);
		}
		rep(j,n) {
			int d=ls->ll[i][j];
			rep(k,n) mine(d,d2[k]+ls->lr[j][k]);
			if (d!=ll[i][j]) 
				ll[i][j]=d, updated=1;
		}
		rep(j,n) {
			int d=inf;
			rep(k,n) mine(d,d2[k]+rs->lr[k][j]-w[k][m]);
			if (d!=lr[i][j])
				lr[i][j]=d, updated=1;
		}
		rep(j,n) {
			d2[j]=inf;
			rep(k,n) mine(d2[j],rs->lr[k][i]+d1[k][j]-w[k][m]);
		}
		rep(j,n) {
			int d=rs->rr[i][j];
			rep(k,n) mine(d,d2[k]+rs->lr[k][j]-w[k][m]);
			if (d!=rr[i][j])
				rr[i][j]=d, updated=1;
		}
	}
	return updated;
}

bool SegTree::chg(int c) {
	if (c<l || r<=c) return 0;
	if (l+1==r) {
		set();
		return 1;
	}
	if (ls->chg(c) || rs->chg(c)) return upd();
	else return 0;
}

void SegTree::set() {
	int s[n+1];s[0]=0;
	rep(i,n) s[i+1]=s[i]+w[i][l];
	rep(i,n) rep(j,n) {
		int a=max(i,j), b=min(i,j);
		ll[i][j]=rr[i][j]=mm[i][j]=lr[i][j]=s[a+1]-s[b];
	}
}

int main() {
	setIO("test");
	
	m=gi;
	rep(i,n) For(j,1,m) w[i][j]=gi;
	root=new SegTree(1,m+1);
	
	for (int q=gi; q--; ) {
		int style=gi;
		if (style==1) {
			int x=gi-1, y=gi, c=gi;
			w[x][y]=c;
			root->chg(y);
		}
		else {
			int x1=gi-1, y1=gi, x2=gi-1, y2=gi;
			if (y1>y2) swap(x1,x2), swap(y1,y2);
			int a[n], b[n], c[n], d[n];
			printf("%d\n", root->ask(x1,y1,x2,y2,a,b,c,d));
		}
	}
	
	return 0;
}
