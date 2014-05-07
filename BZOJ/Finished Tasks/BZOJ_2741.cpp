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

const int inf=~0U>>1, maxn=12000+10, maxm=6000+10, maxs=110+10;
int n, m, cnt=0;
int a[maxn], lab[maxs], next[maxn], s[maxn], res[maxs][maxn];

struct Node {
	int v;
	Node *s[2];
	Node ();
}Tnull, *null=&Tnull, *p[maxn], mem[400000], *c=mem;
Node::Node() { s[0]=s[1]=null; v=0;}

Node *Insert(Node *t, int s) {
	Node *p=c++, *root=p;p->v=t->v+1;
	repD(i,31) {
		Node *now=c++;
		bool d=(1<<i) & s;
		p->s[d^1] = t->s[d^1];
		p->s[d] = now;
		p=now, t=t->s[d];
		p->v = t->v+1;
	}
	return root;
}

int find(Node *l, Node *r, int s) {
	int ans=0;
	repD(i,31) {
		bool d=(1<<i) & s;
		if (r->s[d^1]->v != l->s[d^1]->v) l=l->s[d^1], r=r->s[d^1], ans+=1<<i;
		else l=l->s[d], r=r->s[d];
	}
	return ans;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	For(i,1,n) a[i]=gi, s[i]=s[i-1] ^ a[i];
	int d=(int)sqrt((db) n), tag=1;
	lab[0]=1;
	for ( ;lab[tag-1]<n; ++tag) lab[tag]=min(lab[tag-1]+d, n);
	int j=tag;
	ForD(i,n,1) {
		if (j && i==lab[j-1]) --j;
		next[i]=j;
	}
	p[0]=null;
	For(i,1,n) p[i]=Insert(p[i-1], s[i]);
	
	rep(i,tag) {
		res[i][lab[i]]=0;
		For(j,lab[i]+1,n) res[i][j]=max(res[i][j-1], find(p[lab[i]-1], p[j-1], s[j]));
	}
	Node *ckpoint=c;
	int ans=0;
	rep(i,m) {
		int l=(gi+ans)%n+1, r=(gi+ans)%n+1;
		if (l > r) swap(l, r);
		int k=next[l];
		ans=-1;
		if (lab[k]<=r) ans=res[k][r];
		Node *now=null;
		int t=min(lab[k]-1, r);
		ForD(j,t,l-1) {
			if (now!=null) ans=max(ans, find(null, now, s[j]));
			now=Insert(now, s[j]);
			if (lab[k]<=r) ans=max(ans, find(p[lab[k]-1], p[r], s[j]));
		}
		c=ckpoint;
		printf("%d\n", ans);
	}
	
	return 0;   
}
