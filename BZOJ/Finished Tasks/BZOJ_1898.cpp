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
#include <cstdlib>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (vector<Edge>::iterator i = E[a].begin();i != E[a].end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define mc(a,b) memcpy(a,b,sizeof(a))
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define pf push_front
#define gi gI()

const int inf = ~0U>>1,maxl = 50+10,maxn = 50+10,maxm = 20+10,P = 10000;	
int n,m,K,Start,End;
bool f[maxn][maxn];

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

ll gI() {
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	ll p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

template <class T> void debug(const T &a,const int &n) {rep(i,n) cout << a[i] << " ";puts("");}

struct Matrix {
	int n,m;
	int a[maxl][maxl];
	
	Matrix operator* (const Matrix &B) {
		Matrix tmp;
		fill(tmp.a,0);
		rep(i,n) rep(j,B.m) 
			rep(k,m) tmp.a[i][j] = (tmp.a[i][j] + a[i][k] * B.a[k][j]) % P;
		tmp.n = n,tmp.m = B.m;
		return tmp;
	}
}Reach[12],G,S;

Matrix Unit(int Size) {
	Matrix tmp;
	fill(tmp.a,0);
	tmp.n = tmp.m = Size;
	rep(i,n) tmp.a[i][i] = 1;
	return tmp;
}

Matrix Pow(Matrix A,int t) {
	Matrix res = Unit(n);
	while (t) {
		if (t&1) res = res * A;
		A = A * A;
		t >>= 1;
	}
	return res;
}
	

int main() {
	setIO("test"); 
	
	fill(f,0);
	n = gi,m = gi,Start = gi,End = gi,K = gi;	
	rep(i,m) {
		int x = gi,y = gi;
		f[x][y] = f[y][x] = 1;
	}
	int nFish = gi;
	
	rep(i,12) Reach[i] = Unit(n);
	
	rep(i,nFish) {
		int l = gi,p[4];
		rep(j,l) p[j] = gi;
		rep(j,12) Reach[j].a[p[j%l]][p[j%l]] = 0;
	}
	
	G.n = G.m = n;
	rep(i,n) rep(j,n) G.a[i][j] = f[j][i];
	rep(i,12) Reach[i] = Reach[i] * G;
	G = Unit(n);
	For(i,1,12) G = Reach[i%12] * G;
	
	//S的初始化
	S.n = n,S.m = 1;
	S.a[Start][0] = 1;
	
	Matrix tmp = Unit(n);
	tmp = Pow(G,K/12) * tmp;
	For(i,1,K%12) tmp = Reach[i] * tmp;
	
	S = tmp * S;
	
	printf("%d\n", S.a[End][0]);
		
	return 0;
}
