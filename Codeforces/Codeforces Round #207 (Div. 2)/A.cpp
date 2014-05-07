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

const int inf = ~0U>>1,maxT = 1000000+10;
int n,m;

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

void pI(ll a) {
	if (a == 0){
		putchar(0);
		return ;
	}
	char c[20];
	int l = 0;c[0] = 0;
	
	for (;a;a/=10) c[l++] = a%10;
	repD(i,l) putchar(c[i]);
}

template <class T> void debug(const T &a,const int &n) {rep(i,n) cout << a[i] << " ";puts("");}

struct sTree {
    int n,h;
    ll a[maxT],Tag[maxT];
 
    void init(const int &_n) {
        n = _n;
        for (h = 1;(1 << h) < n+2; ++ h) ;
        
        fill(a,0),fill(Tag,0);
    }
     
    void Pass_Down(const int&x) {
        #define y (x<<1)
        #define z (x<<1)+1
        
        if (Tag[x] == 0) return ;
        Pass_Down(y),Pass_Down(z);
        
        if (y >= (1<<h)) {
			if (a[y] == 0) a[y] = Tag[x];
		}
		else Tag[y] = Tag[x];
		
		if (z >= (1<<h)) {
			if (a[z] == 0) a[z] = Tag[x];
		}
		else Tag[z] = Tag[x];
		
		Tag[x] = 0;
        
        #undef y
        #undef z
    }
     
    void Pass_to_Leaf(int x) {
        repD(i,h-1) Pass_Down(x >> (i+1));
    }
     
    void Add(int x,int y,ll c) {
        int l = x + (1<<h) - 1,r = y + (1<<h) + 1;
        Pass_to_Leaf(l),Pass_to_Leaf(r);
        while (l + 1 < r) {
            if (!(l&1)) 
				if (l>=(1<<h)) {
					if (a[l^1] == 0) a[l^1] = c;
				}
				else Pass_Down(l^1),Tag[l^1] = c;
            if (r&1) 
				if (r>=(1<<h)) {
					if (a[r^1] == 0) a[r^1] = c;
				}
				else Pass_Down(r^1),Tag[r^1] = c;
            l >>= 1,r >>= 1;
        }
    }
    int Ask(int x) {
		x += (1<<h);
		Pass_to_Leaf(x);
		return a[x];
	}
	void Change(int x,int c) {
		x += (1<<h);
		Pass_to_Leaf(x);
		a[x] = c,Tag[x] = 0;
	}
}T;


int main() {
	setIO("test"); 
	
	n = gi,m = gi;
	T.init(n);
	while (m--) {
		int l = gi,r = gi,c = gi;
		T.Add(l,r,c);
		T.Change(c,0);
	}
	rep(i,n) {
		cout << T.Ask(i+1);
		(i == n-1) ? puts("") : printf(" ");
	}
	
	return 0;
}
