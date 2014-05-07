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

typedef long long ll;
typedef double db;
typedef long double ld;
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
//#define max(a,b) (((a)>(b))?(a):(b))
//#define min(a,b) (((a)>(b))?(b):(a))
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
ll gI() {
	char c=getchar();
	while ((c<'0' || c>'9')&&c!='-') c=getchar();
	ll flag=1,p=0;
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

const int inf=~0U>>1,maxT=500000,maxn=100000+10,maxv=200000+10;
int n,cnt=0,ans1,V,tag;
int d[maxn],que[maxn],ans[maxn];
int x[maxn],style[maxn],w[maxn],L[maxn],R[maxn];
map<int,int> f;
struct sTree {
	int h;
	int MAX[maxT],MIN[maxT],tagMAX[maxT],tagMIN[maxT];
 
	void init(const int n) {
		for (h = 1;(1<<h)<n+2; ++h) ;
		fill(MIN,127), fill(MAX,128), fill(tagMAX,0), fill(tagMIN,0);
	}
	void refresh(const int&x) {
		MAX[x]=max(MAX[x<<1],MAX[(x<<1)+1]);
		MIN[x]=min(MIN[x<<1],MIN[(x<<1)+1]);
	}
	void tagIt(const int&x,const int&c) {
		tagMAX[x]=(tagMAX[x]==0)?c:max(tagMAX[x],c);
		tagMIN[x]=(tagMIN[x]==0)?c:min(tagMIN[x],c);
		MAX[x]=max(MAX[x],tagMAX[x]);
		MIN[x]=min(MIN[x],tagMIN[x]);
	}
	void relax(const int&x) {
		int y = (x<<1),z = y+1;
		if (tagMAX[x]) {
			tagIt(y,tagMAX[x]), tagIt(z,tagMAX[x]);
			tagMAX[x]=0;
		}
		if (tagMIN[x]) {
			tagIt(y,tagMIN[x]), tagIt(z,tagMIN[x]);
			tagMIN[x]=0;
		}
	}	 
	void Pass_to_Leaf(int x) {
		repD(i,h-1) relax(x >> (i+1));
	}	 
	void Update(int x) {
		for (x>>=1;x;x>>=1) refresh(x);
	}	 
	Pair Ask(int l,int r) {
		int v1=-inf,v2=inf;
		l+=(1<<h)-1,r+=(1<<h)+1;
		Pass_to_Leaf(l),Pass_to_Leaf(r); 
		while (l+1<r) {
			if (!(l&1)) {
				v1=max(v1,MAX[l^1]);
				v2=min(v2,MIN[l^1]);
			}
			if (r&1) {
				v1=max(v1,MAX[r^1]);
				v2=min(v2,MIN[r^1]);
			}
			l>>=1, r>>=1;
		}
		return mp(v1,v2);
	}	 
	void Chg(int x,int y,int c) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		Pass_to_Leaf(l),Pass_to_Leaf(r);
		while (l+1<r) {
			if (!(l&1)) tagIt(l^1,c);
			if (r&1) tagIt(r^1,c);
			l>>=1,r>>=1;
		}
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		Update(l),Update(r);
	}
}T;
struct Vertex {
	int x,y,i;
};
struct Line {
	Vertex s,t;
	int i;
}l[maxn];
struct Edge {
	int y;
	Edge *next;
	Edge () {}
	Edge (int _y,Edge *_next) : y(_y), next(_next) {}
}*h[maxn];
struct Point {
	int x,i;bool flag;
	Point(){}
	Point(int _x,int _i,bool _flag) : x(_x), i(_i), flag(_flag) {}
	inline bool operator< (const Point& b) const {
		return x<b.x || (x==b.x && flag<b.flag);
	}
}q[maxv];
inline bool operator< (const Line&a, const Line&b) {
	ld mid=(max(a.s.x,b.s.x)+min(a.t.x, b.t.x))/2;
	ld ta=(mid-a.s.x)/(a.t.x-a.s.x)*(a.t.y-a.s.y)+a.s.y;
	ld tb=(mid-b.s.x)/(b.t.x-b.s.x)*(b.t.y-b.s.y)+b.s.y;
	return ta<tb;
}

void Add_Edge(int x,int y) {
	++d[y];
	h[x]=new Edge(y,h[x]);
}

int getans(int s1,int s3) {
	int res=n;
	T.init(tag);
	repD(i,n) {
		int u=x[i];
		if (style[i]==s1 || style[i]==s3) {
			Pair t=T.Ask(L[u], R[u]-1);
			if (style[i]==s1 && t.first>w[u]) res=i;
			if (style[i]==s3 && t.second<w[u]) res=i;
		}
		T.Chg(L[u], R[u]-1, w[u]);
		
	}
	return res;
}

void work() {
	set<Line> tree;tree.clear();
	fill(h,0);
	V=0;
	rep(i,n) {
		q[V++]=Point(l[i].s.x,i,1);
		q[V++]=Point(l[i].t.x,i,0);
	}

	sort(q,q+V);
	fill(d,0);

	rep(i,V) {
		if (q[i].flag) 
			tree.insert(l[q[i].i]);
		set<Line>::iterator it=tree.find(l[q[i].i]), tmp=it;
		++it;
		if (it!=tree.end())
			Add_Edge(it->i, tmp->i);
		
		it=tmp;
		if (it!=tree.begin())
			Add_Edge(tmp->i, (--it)->i);
		
		if (!q[i].flag)
			tree.erase(tmp);
	}
	int r=0;
	rep(i,n) if (!d[i]) que[r++]=i;
	rep(i,r) {
		int x=que[i];
		ForE(j,x) {
			int y=j->y;
			if (!--d[y]) que[r++]=y;
		}
	}

	f.clear();
	rep(i,n) 
		f[l[i].s.x]=1, f[l[i].t.x]=1;
	
	tag=0;
	ForV(i,f) 
		i->second=++tag;
	rep(i,n) {
		L[i]=f[l[i].s.x];
		R[i]=f[l[i].t.x];
	}	
	rep(i,n) w[que[i]]=i+1;
	
}

int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) {
		l[i].i=i;
		l[i].s.x=gi, l[i].s.y=gi, l[i].t.x=gi, l[i].t.y=gi;
		if (l[i].s.x>l[i].t.x) swap(l[i].s, l[i].t);
	}
	
	rep(i,n) x[i]=gi-1, style[i]=gi;
	
	//按照x计算拓补序
	work();
	ans1=n;
	ans1=min(ans1,getans(3,1));
	rep(i,n) ans[i]=que[i];
	//按照y计算拓补序
	rep(i,n) {
		swap(l[i].s.x, l[i].s.y);
		swap(l[i].t.x, l[i].t.y);
		if (l[i].s.x>l[i].t.x) swap(l[i].s, l[i].t);
	}
	work();
	ans1=min(ans1,getans(0,2));
	printf("%d\n", ans1+1);
	rep(i,n) printf("%d 1\n", ans[i]+1);
	return 0;
}
