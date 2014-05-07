#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define fill(a,b) memset(a,b,sizeof(a))
#define gI gi()

const int inf = ~0U>>1,maxn = 500000+10,maxT = 800000+10;
int n,m,tot,H,r = 0;
int h[maxn],Q[maxn],L[maxn],R[maxn],pos[maxn],A[maxn],B[maxn],ans[maxn],f[maxn],T[maxT];
struct Edge
{
	int to,next;
}E[maxn];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int gi()
{
	char c = getchar();
	while (c != '-' && (c > '9' || c < '0')) c = getchar();
	int n = 0,s = 1;if (c == '-') s = -1,c = getchar();
	while (c >= '0' && c <= '9') n = n*10 + c - '0',c = getchar();
	return n*s;
}

void Pass_Down(int x)
{
	if (T[x] != 0) T[x<<1] += T[x],T[(x<<1)+1] += T[x],T[x] = 0;
}

void Pass_to_Leaf(int x)
{
	repD(i,H-1) Pass_Down(x>>(i+1));
}

void addedge(int a,int b)
{
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot;
}

void getQ(int x)
{
	Q[r++] = x;
	ForE(i,x) getQ(E[i].to);
}

void Add(int x,int y,int p)
{
	int l = x+(1<<H)-1,r = y+(1<<H)+1;
	Pass_to_Leaf(l),Pass_to_Leaf(r);
	while (l^r^1) {
		if (l%2==0) T[l+1] += p;
		if (r%2==1) T[r-1] += p;
		l>>=1,r>>=1;
	}
}

int Ask(int x)
{
	x+=(1<<H);
	Pass_to_Leaf(x);
	return T[x];
}
 
int main()
{
	//setIO("test"); 
	
	scanf("%d", &n);
	rep(i,n) h[i] = -1;
	for (H = 1;(1<<H)<n+2;++H);
	rep(i,n-1) {
		int a,b;
		scanf("%d %d", &a, &b),--a,--b;
		if (a > b) swap(a,b);f[b] = a;addedge(a,b);
	}
	
	getQ(0);	
	rep(i,n) L[Q[i]] = R[Q[i]] = pos[Q[i]] = i;
	repD(i,n) L[f[Q[i]]] = min(L[f[Q[i]]],L[Q[i]]),R[f[Q[i]]] = max(R[f[Q[i]]],R[Q[i]]);
	
	scanf("%d\n", &m);m+=n-1;
	rep(i,m) {
		char c = getchar();
		//printf("%c\n", c);
		if (c == 'W') scanf("%d\n", &B[i]),--B[i],A[i] = -1;
		else scanf("%d %d\n", &A[i], &B[i]),--A[i],--B[i];
	}
	
	repD(i,m) 
		if (A[i] == -1) ans[i] = Ask(pos[B[i]]+1);
		else {
			if (A[i]>B[i]) swap(A[i],B[i]);
			Add(L[B[i]]+1,R[B[i]]+1,1);
		} 
		
	rep(i,m) if (A[i]==-1) printf("%d\n", ans[i]);
	
	return 0;
}
