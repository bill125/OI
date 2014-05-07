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
typedef pair<int,ll> Pair;
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

const int inf=~0U>>1, maxn=250+10, maxm=maxn, maxp=3000+10;
int n, m, tag;
ll d[7], w[7];

struct CostFlow {
    int S,T,n;
    struct Edge {
        Edge *r,*next;
        int y;ll c,f;
        Edge () {}
        Edge (Edge *_next, int _y,ll _c,ll _f) : next(_next), y(_y), c(_c), f(_f) {}
    }*h[maxp],*prev[maxp];
    void init(int _n,int _S,int _T) {
        n=_n, S=_S, T=_T;
        fill(h,0);
    }
    void Add_Edge(int x,int y,ll f,ll c) {
        Edge *e1=h[x]=new Edge(h[x],y,c,f),*e2=h[y]=new Edge(h[y],x,-c,0);
        e1->r=e2, e2->r=e1;
    }
    ll Find() {
        deque<Pair> q;q.clear();
        vector<ll> d(n,1000000000000LL);
        d[S]=0;q.pb(mp(S,0));
        for (;;) {
            Pair now=mp(0,-1);
            while (!q.empty()) {
                now=q.front();q.pop_front();
                if (now.second==d[now.first]) break;
            }
            int x=now.first;
            if (now.second!=d[x]) break;
            ForE(e,x) if (e->f) {
                int y=e->y;
                if (d[x]+e->c<d[y]) {
                    d[y]=d[x]+e->c;
                    prev[y]=e;
                    if (q.empty() || d[y]<q.front().second) q.push_front(mp(y,d[y]));
                    else q.pb(mp(y,d[y]));
                }
            }
        }
        if (d[T]==1000000000000LL) return -1;
        ll now_flow=1000000000000LL;
        for (int x=T; x!=S; x=prev[x]->r->y) now_flow=min(now_flow, prev[x]->f);
        for (int x=T; x!=S; x=prev[x]->r->y)
            prev[x]->f-=now_flow, prev[x]->r->f+=now_flow;
        return d[T]*now_flow;
    }
    ll Run() {
        ll res=0;
        for (;;) {
            ll t=Find();
            if (t==-1) break;
            res+=t;
        }
        return res;
    }
}A;

int main() {
	setIO("test");
	
	m=gi, n=gi;
	
	int s=0, t=n+m+1;
	A.init(n+m+2, s, t);
	rep(i,n) {
		int c=gi;
		A.Add_Edge(s, i+1, c, 0);
	}
	rep(i,m) rep(j,n) {
		int a=gi;
		if (a) A.Add_Edge(j+1, i+n+1, inf, 0);
	}
	
	rep(i,m) {
		int s=gi;
		For(j,1,s) d[j]=gi;
		For(j,1,s+1) w[j]=gi;
		d[0]=0, d[s+1]=inf;
		For(j,1,s+1) A.Add_Edge(i+n+1, t, d[j]-d[j-1], w[j]);
	}
	
	printf("%I64d\n", A.Run());
	
	return 0;   
}
