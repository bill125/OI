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

const int inf=~0U>>1, maxn=50000+10, maxp=maxn<<1;
int n,k,ans=0;
ll m;
template < class T > struct Priority_Queue {
	vector<T> q;
	void init() { q.clear(); }
	int size() { return q.size(); }
	T top() { return q.front(); }
	T top2() { return -q.front(); }
	void push(T a) { q.push_back(a); push_heap(q.begin(), q.end()); }
	void push2(T a) { q.push_back(-a); push_heap(q.begin(), q.end()); }
	void pop() { pop_heap(q.begin(), q.end()), q.pop_back(); }
	bool empty() { return q.empty(); }
};

Priority_Queue<ll> Q, Q1;
ll sum[maxn], MaxC[maxn], tot[maxn];
struct Cow {
	ll p, c;
	bool operator<(const Cow &a) const { return p-c<a.p-a.c || (p-c==a.p-a.c && p<a.p); }
}a[maxn];

int main() {
	setIO("test");
	
	n=gi, k=gi, m=gi;
	rep(i,n) a[i].p=gi, a[i].c=gi, a[i].c=a[i].p-a[i].c;
	sort(a, a+n);
	Q.init();
	rep(i,n) {
		sum[i]=(!i)?a[i].p:(sum[i-1]+a[i].p);
		MaxC[i]=(!i)?0:MaxC[i-1];
		if (Q.size()<k-1) Q.push(a[i].c), MaxC[i]+=a[i].c;
		else if (i && !Q.empty() && Q.top()<a[i].c) {
			MaxC[i]=MaxC[i-1]-Q.top()+a[i].c;
			Q.pop(), Q.push(a[i].c);
		}
		tot[i]=sum[i]-a[i].c;
		if (i) tot[i]-=MaxC[i-1];
	}

	ll all=0;int cnt=0;
	Q.init(), Q1.init();
	repD(i,n) {
		if (tot[i]>m) {Q1.push2(a[i].p);continue;}
		while (!Q1.empty() && all+Q1.top2()<=m-tot[i]) 
			all+=Q1.top2(), Q.push(Q1.top2()), Q1.pop(), ++cnt;
		ans=max(ans, cnt+i+1);
		if (!Q.empty() && a[i].p<Q.top()) {
			all=all-Q.top()+a[i].p;
			Q1.push2(Q.top());
			Q.pop(), Q.push(a[i].p);
		}
		else Q1.push2(a[i].p);
	}
	printf("%d\n", ans);
	
	return 0;
}
