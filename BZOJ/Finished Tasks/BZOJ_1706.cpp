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
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define pf push_front
#define gi gI()

const int inf = ~0U>>1,maxl = 200+10;
int n,m,Start,End,Index = 0;
map<int,int> Tag;

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
    ll a[maxl][maxl];
     
    Matrix operator* (const Matrix &B) {
        Matrix tmp;
        fill(tmp.a,20);
        rep(i,n) rep(j,B.m) 
            rep(k,m) tmp.a[i][j] = min(tmp.a[i][j],a[i][k] + B.a[k][j]);
        tmp.n = n,tmp.m = B.m;
        return tmp;
    }
    void debug() {
        printf("%d %d\n", n, m);
        rep(i,n) {
            rep(j,m) printf("%lld ", a[i][j]);
            puts("");
        }
        puts("==================");
    }
}G,S;
 
Matrix Pow(Matrix A,int t) {
    Matrix res;
    bool flag = 1;
    while (t) {
        if (t&1) 
			if (flag) res = A,flag = 0;
			else res = res * A;
        A = A * A;
        t >>= 1;
    }
    return res;
}


int NewTag(int a) {
	if (!Tag.count(a)) Tag[a] = Index++;
	return Tag[a];
}

int main() {
	setIO("test"); 
	
	n = gi,m = gi,Start = NewTag(gi),End = NewTag(gi);
	fill(G.a,20);
	rep(i,m) {
		int c = gi,a = NewTag(gi),b = NewTag(gi);
		G.a[a][b] = G.a[b][a] = c;
	}
	
	G.n = G.m = Index;
	
	S.n = Index,S.m = 1;
	fill(S.a,20);
	S.a[Start][0] = 0;

	Matrix ans = Pow(G,n)*S;
	
	printf("%lld\n", ans.a[End][0]);
	
	return 0;
}
