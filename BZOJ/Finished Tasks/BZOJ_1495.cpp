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

const int inf = ~0U>>3,maxn = (1<<10)+10;
int n,m;
int A[maxn],C[maxn],F[maxn][maxn],S[maxn][10+2]={},dp[maxn*2][maxn*2];
bool pay[maxn];

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

void getS(int i,int j)
{
    int a = i+m,b = j+m;
    For(d,1,n)
        if ((a>>d) == (b>>d)) {
			S[i][n-d] += F[i][j];
			S[j][n-d] += F[i][j];
            return;
        }
}

struct State
{
    int Dep;
    int Set,numA;
    State(int _Dep,int _Set,int _numA):
        Dep(_Dep),Set(_Set),numA(_numA){}
    State(){}
    bool Legal() {
        return (m>>(Dep))>=numA;
    }
    int Hash() {
        return (numA<<Dep)+Set;
    }
};

int Dp(int at,State st)
{
    if (!st.Legal()) return inf;
    int &mem = dp[at][st.Hash()];
    if (mem > 0) return mem;
    if (at >= m) {
        int i = at-m;
        int rA = 0,rB = 0;
        if (A[i]) rA = C[i];
        else rB = C[i];
        rep(j,n)
            if (st.Set & (1<<j))
                rB += S[i][j];
            else
                rA += S[i][j];
        if (st.numA)
            return mem = rA;
        else
            return mem = rB;
    }
    else  {
        int nA = st.numA,ret;
        int L = at*2,R = L+1;
        int type = st.numA >= (m>>(st.Dep+1));
        int NewSet = st.Set | (type<<(st.Dep));
        mem = inf;
        rep(La,nA+1) {
            ret = Dp(L,State(st.Dep+1,NewSet,La)) + Dp(R,State(st.Dep+1,NewSet,nA-La));
            mem = min(ret,mem);
        }
    }
    return mem;
}

int main() {
	setIO("test"); 
	
	n = gi;m = 1<<n;
    rep(i,m) A[i] = gi;
    rep(i,m) C[i] = gi;
    rep(i,m)
        For(j,i+1,m-1)
            F[i][j] = gi;
            
    rep(i,m)
		For(j,i+1,m-1)
            getS(i,j);
    
    fill(dp,-1);
    int ans = inf;
    rep(A,m+1) 
        ans = min(ans,Dp(1,State(0,0,A)));
    
    printf("%d\n", ans);
	
	return 0;
}
