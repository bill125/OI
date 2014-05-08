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
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxp=1500000+10, maxn=500000+10, maxe=2000000+10, maxt=4000000;
int n, Index=1;
int p[maxp], sz[maxp], x[maxn][3], q[maxp], dep[maxp];
int s[maxp], hs[maxn], id[maxn], an[maxn];

struct Edge {
	int y;
	Edge *next;
}*h[maxn], mem[maxe], *e=mem;
Edge*makeedge(int x,int y) {
	e->y=y, e->next=h[x];
	return e++;
}
void Add_Edge(int x,int y) {
	h[x]=makeedge(x, y);
}

void refresh(int t) {
	s[t]=0;
	rep(i,3) s[t]+=(x[t][i]>=n) ? (s[x[t][i]]) : (s[x[t][i]]>=2);
}

struct Node {
	int sz, cov;
	int R[3], v;
	void covIt(int k) { 
		//printf("%d\n", k);
		v=k,cov=k;
		//printf("%d\n", v);
		R[1]=R[2]=0;
		if (k<3) R[k]=sz;
	}
	Node () { sz=cov=v=-1; }
}t;
Node operator+(Node &l, Node &r) {
	if (l.sz==-1) { t=r;t.cov=-1; return t; }
	if (r.sz==-1) { t=l;t.cov=-1; return t; }
	t.sz=l.sz+r.sz;t.cov=-1;
	For(i,1,2) t.R[i]=(r.R[i]==r.sz) ? (r.sz + l.R[i]) : r.R[i]; 
	return t;
}
struct SegTree{
	int h;
	Node a[maxt];
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		rep(i,n) a[i+(1<<h)+1].sz=1;
		repD(i,(1<<h)) ref(i);
	}
	void relax(int x) {
		int y=x<<1, z=y+1;
		if (a[x].cov!=-1) {
			if (a[y].sz!=-1) a[y].covIt(a[x].cov);
			if (a[z].sz!=-1) a[z].covIt(a[x].cov);
			a[x].cov=-1;
		}
	}
	void ref(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
	void pass_down(int x) {	repD(i,h-1) relax(x>>(i+1)); }
	void upd(int x) { for (x>>=1; x; x>>=1) ref(x); }
	void cover(int x,int y,int k) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass_down(l), pass_down(r);
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		while (l+1 < r) {
			if (!(l&1)) a[l^1].covIt(k);
			if (r&1) a[r^1].covIt(k);
			l>>=1, r>>=1;
		}
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		upd(l), upd(r);
	}
	void cover(int x,int k) {
		x+=(1<<h);
		pass_down(x);
		//cut;
		a[x].covIt(k);
		//printf("  %d\n", a[x].v);
		upd(x);
	}
	Node query(int x) {
		x+=(1<<h);pass_down(x);
		return a[x];
	}
	Node query(int l,int r) {
		l+=(1<<h)-1, r+=(1<<h)+1;
		pass_down(l), pass_down(r);
		Node L,R;L.sz=R.sz=-1;
		while (l+1<r) {
			if (!(l&1)) L=L+a[l^1];
			if (r&1) R=a[r^1]+R;
			l>>=1, r>>=1;
		}
		return L+R;
	}
}T;

int stack[maxp];
void fuckthis(int s) {
	int r=1;
	stack[0]=s;
	rep(i,r) {
		int x=stack[i];
		id[x]=Index++; an[x]=s;
		if (hs[x] == -1) break;
		stack[r++]=hs[x];
	}
}

void modify(int x,int k) {
	for (;x!=-1;) {
		if (an[x] == x) {
			//puts("XX");
			Node tmp=T.query(id[x]);
			if (tmp.v == k) {
				//printf("%d\n", x+1);
				T.cover(id[x], 3-k);
				x=p[x];
			}
			else {
				T.cover(id[x], (k==1) ? (tmp.v+1) : (tmp.v-1));
				break;
			}
		}
		else {
			int y=an[x];
			Node tmp=T.query(id[y], id[x]);
			if (tmp.sz == tmp.R[k]) {
				T.cover(id[y], id[x], 3-k);
				x=p[y];
			}
			else {
				y = id[x] - tmp.R[k];
				T.cover(y + 1, id[x], 3-k);
				tmp = T.query(y);
				T.cover(y, (k==1) ? (tmp.v+1) : (tmp.v-1));
				break;
			}
		}
	}
}

int main() {
	setIO("neuron");
	
	n=gi;
	T.init(n);
	rep(i,n) 
		rep(j,3) {
			x[i][j]=gi-1;
			p[x[i][j]]=i;
			if (x[i][j]>=n) ++sz[i];
			Add_Edge(i, x[i][j]);
		}

	int r=1;q[0]=0;
	rep(i,r) {
		int x=q[i];
		ForE(e, x) {
			int y=e->y;
			if (y>=n) continue;
			q[r++]=y;
		}
	}

	p[0]=-1;
	For(i,n,3*n) s[i]=gi;
	repD(i,n) refresh(q[i]);
	rep(i,n) hs[i]=-1;
	repD(i,r) {
		int t=q[i];
		rep(j,3) sz[t] += sz[x[t][j]];
		if (p[t]>=0) {
			if (hs[p[t]]==-1 || sz[t] > sz[hs[p[t]]]) {
				hs[p[t]] = t;
			}
		}
	}
	
	rep(i,3*n+1) id[i]=-1;
	rep(i,n) {
		int x=q[i];
		if (id[x]!=-1) continue;
		fuckthis(x);
	}
	rep(i,n) {
		T.cover(id[i], s[i]);
	}
	Node tmp=T.query(id[n]);
	
	for (int q=gi; q--; ) {
		int x=gi-1;
		s[x]^=1;
		modify(p[x], 2-s[x]);
		printf("%d\n", T.query(id[0]).v>=2);
	}
	
	return 0;   
}
