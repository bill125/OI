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

const int inf=~0U>>1, maxn=200000+10;
int n;
struct Quest {
	int l, r, id;
}A[maxn], B[maxn], C[maxn];
bool chosen[maxn];
int L[maxn], R[maxn], num[maxn];

bool cmp(int x,int y) {
	return A[x].id < A[y].id;
}

bool cmp1(const Quest & l, const Quest & r) {
	return l.l < r.l || l.l == r.l && l.r > r.r;
}

bool cmp2(const Quest & l, const Quest & r) {
	return l.r < r.r || l.r == r.r && l.l > r.l;
}

int work(int l,int r) {
	For(i,l,r) B[i]=A[i], C[i]=A[i];
	sort(B+l, B+r+1, cmp2);
	sort(C+l, C+r+1, cmp1);
	
	int RightMost=-1, LeftMost=1000000001;
	For(i,l,r) {
		L[i]=(i==l)?0:L[i-1];
		if (B[i].l > RightMost) {
			RightMost=B[i].r;
			++L[i];
		}
	}
	ForD(i,r,l) {
		R[i]=(i==r)?0:R[i+1];
		if (C[i].r < LeftMost) {
			LeftMost=C[i].l;
			++R[i];
		}
	}
	For(i,l,r) num[i]=i;
	sort(num+l, num+r+1, cmp);
	int ans=L[r];
	
	For(i,l,r) {
		int x=num[i];
		int cnt=1;
		int l1=l-1, r1=r+1;
		while (l1 + 1 < r1) {
			int m = l1 + r1 >> 1;
			if (B[m].r < A[x].l) l1=m;
			else r1=m;
		}
		cnt += (l1!=l-1) ? L[l1] : 0;
		
		int l2=l-1, r2=r+1;
		while (l2 + 1 < r2) {
			int m = l2 + r2 >> 1;
			if (C[m].l > A[x].r) r2=m;
			else l2=m;
		}
		cnt += (r2!=r+1) ? R[r2] : 0;
		
		if (cnt == ans) {
			chosen[A[x].id] = 1;
			For(i,l,l1) A[i]=B[i];
			For(i,r2,r) A[i]=C[i];
			if (l1!=l-1) work(l, l1);
			if (r2!=r+1) work(r2, r); 
			return ans;
		}
	}
	
	return ans;
}

int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) A[i].l=gi, A[i].r=gi, A[i].id=i+1;

	int ans=work(0,n-1);	
	printf("%d\n", ans);
	For(i,1,n) if (chosen[i]) printf("%d%c", i, (--ans==0) ? '\n' : ' ');
	
	return 0;   
}
