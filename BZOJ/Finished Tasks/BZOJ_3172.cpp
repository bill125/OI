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

const int inf=~0U>>1, maxn=200+10, maxl=10000000+10;
int n,r=0;
char c[maxl], s[maxl];

struct Node {
	Node *s[26], *Fail;
	int tot;
	Node () ;
}*C, Tnull, *null=&Tnull, *root=null, *ans[maxn], *q[maxl];
Node::Node() { tot=0, Fail=null; rep(i,26) s[i]=null; }
Node *mk() { return new Node; }

Node* Insert(int l,char c[]) {
	Node *t=root;
	rep(i,l) {
		int k=c[i]-'a';
		if (t->s[k]==null) t->s[k]=mk();
		t=t->s[k];
	}
	return t;
}
void PreWork() {
	r=1;q[0]=root;
	rep(i,r) {
		Node *x=q[i];
		rep(j,26) if (x->s[j]!=null) { 
			Node *t=x->Fail;
			for (; t!=null && t->s[j]==null; t=t->Fail) ;
			x->s[j]->Fail=(t==null)?root:t->s[j];
			q[r++]=x->s[j];
		}
	}
}

int main() {
	setIO("test");
	
	n=gi;
	int j=0;
	root=mk();
	rep(i,n) {
		int l=gs(c);
		ans[i]=Insert(l,c);
		s[j++]=' ';
		rep(k,l) s[j++]=c[k];
	}
	
	PreWork();
	int l=strlen(s);
	
	Node *x;
	rep(i,l) {
		if (s[i]==' ') x=root;
		else {
			int k=s[i]-'a';
			Node *t=x;
			for (;t!=null && t->s[k]==null; t=t->Fail) ;
			if (t!=null) x=t->s[k], ++x->tot;
			else x=root;
		}
	}
	repD(i,r) q[i]->Fail->tot+=q[i]->tot;
	rep(i,n) printf("%d\n", ans[i]->tot);
	
	return 0;
}
