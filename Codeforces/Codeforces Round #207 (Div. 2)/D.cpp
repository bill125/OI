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

const int inf = ~0U>>1,maxn = 70000+10;
int n,s;
int a[maxn],num[maxn],ans[maxn],ans2[maxn],c[maxn];
bool v[maxn],v2[maxn];
int use[maxn];

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

bool cmp(int x,int y) {
	return a[x] > a[y];
}

int main() {
	setIO("test"); 
	
	n = gi,s = gi;
	rep(i,n) {
		a[i] = gi;
		num[i] = i;
	}
	
	sort(num,num + n,cmp);
	
	fill(v,0);
	
	v[a[num[0]]] = 1;
	vector<int> q;q.clear();
	q.pb(a[num[0]]);use[a[num[0]]] = num[0];
	
	int l = 0,r = -1;
	For(i,1,n-1) {
		if (a[num[i]] == a[num[i-1]]) {
			l = r+1,r = q.size()-1;
		}
		else {
			l = 0,r = q.size()-1;
		}
		For(j,l,r) {
			int t = q[j] + a[num[i]];
			if (t > s) continue;
			if (!v[t]) {
				v[t] = 1;
				use[t] = num[i];
				q.pb(t);
				if (t == s) break;
			}
		}
		if (v[s]) break;
	}	
	
	fill(v2,0);
	
	if (!v[s]) {
		puts("-1");
		return 0;
	}
	else {
		fill(ans,0);
		for (int j = s;j > 0;j -= a[use[j]]) {
			ans[use[j]] = 0;
			v2[use[j]] = 1;
		}
		int last = 0;
		For(i,1,n-1) if (!v2[num[i]]) {
			ans2[num[last]] = num[i];
			ans[num[last]] = 1;
			last = i;
		}
		rep(i,n) {
			if (ans[i] == 0) {
				printf("%d 0\n", a[i]);
			}
			else {
				printf("%d 1 %d\n",a[i]-a[ans2[i]],ans2[i]+1);
			}
		}
	}
	
	return 0;
}
