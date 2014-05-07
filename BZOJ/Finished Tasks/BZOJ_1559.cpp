// Author: bill125
// ntr czr
// orz zyx
// using namespace inline

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
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1, maxn=25+4, maxM=(1<<10)+10, maxlen=10+10, maxp=100+10;
int n,m,tot,cnt=0;
char c[maxlen];
struct Node {
	Node *s[26], *Fail, *jump[26];
	int M;
	ll dp[maxn][maxM];
	Node ();
}Tnull, *null=&Tnull, *root, *q[maxp];
string anss[maxM];
Node::Node() { Fail=null, M=0; rep(i,26) s[i]=jump[i]=null; fill(dp,0);}
Node *mk() { return new Node; }
Node *Insert(int l,char c[]) {
	Node *t=root;
	rep(i,l) {
		int k=c[i]-'a';
		if (t->s[k]==null) t->s[k]=mk();
		t=t->s[k];
	}
	return t;
}
void PreWork() {
	tot=1;q[0]=root;
	rep(i,tot) {
		Node* x=q[i];
		rep(j,26) 
			if (x->s[j]!=null) {
				Node *t=x->Fail;
				for (;t!=null && t->s[j]==null; t=t->Fail) ;
				x->s[j]->Fail=(t==null)?root:t->s[j];
				x->jump[j]=x->s[j];
				q[tot++]=x->s[j];
			}
			else {
				x->jump[j]=(x->Fail->jump[j]==null)?root:x->Fail->jump[j];
			}
		x->M|=x->Fail->M;
	}
}
void find(Node *t,int i,int M,string now) {
	if (i==0) {
		anss[cnt++]=now;
		return ;
	}
	rep(j,tot) {
		Node *x=q[j];
		if (!x->dp[i-1][M]) continue;
		rep(k,26) if (x->jump[k]==t) {
			char c=k+'a';
			find(x,i-1,M,c+now);
		}
	}
	if (!(M&t->M)) return ;
	M^=t->M;
	rep(j,tot) {
		Node *x=q[j];
		if (!x->dp[i-1][M]) continue;
		rep(k,26) if (x->jump[k]==t) {
			char c=k+'a';
			find(x,i-1,M,c+now);
		}
	}
}
int main() {
	setIO("test");
	
	n=gi, m=gi;
	root=mk();
	rep(i,m) {
		int l=gs(c);
		Node *t=Insert(l,c);
		t->M|=1<<i;
	}
	PreWork();
	
	root->dp[0][0]=1;
	rep(i,n) {
		rep(j,tot) {
			Node *x=q[j];
			rep(k,(1<<m)) if (x->dp[i][k]) {
				rep(t,26) if (x->jump[t]!=null)
					x->jump[t]->dp[i+1][k|x->jump[t]->M]+=x->dp[i][k];
			}
		}
	}
	
	ll ans=0;
	rep(j,tot) ans+=q[j]->dp[n][(1<<m)-1]; 
	printf("%lld\n", ans);

	if (ans<=42) {
		rep(i,tot) if (q[i]->dp[n][(1<<m)-1]) find(q[i], n, (1<<m)-1, "");
		sort(anss, anss+cnt);
		rep(i,cnt) cout << anss[i] << endl;
	}
	
	return 0;
}
