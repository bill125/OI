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

const int inf = ~0U>>1,maxn = 8+5,maxs = 20+10,maxt = 400000+10;
int n,m,s,t,r,lA,rA,Lcnt = 0,Target = -1,cnt = 0;
ll d;
int dx[4] = {0,1,0,-1},dy[4] = {1,0,-1,0};
struct Tower {
	int x,y;
}T[maxs];
struct Ant {
	ll hp,ihp;
	int x,y,lx,ly,t,time;
}A[maxt];
int I[maxn][maxn];
bool v[maxn][maxn];

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

db Fast_Pow(db a,int b) {
	db res = 1;
	while (b) {
		if (b&1) res *= a;
		a *= a;
		b >>= 1;
	}
	return res;
}

bool NoAnt(int x,int y) {
	For(i,lA,rA) 
		if (A[i].x == x && A[i].y == y) 
			return 0;
	return 1;
}

bool legal(int x,int y) {
	return (x >= 0 && x <= n && y >= 0 && y <= m && NoAnt(x,y) && v[x][y]);
}

void Move(Ant & a) {
	int tmp = -inf,nx,ny,nk;
	rep(k,4) {
		int tx = a.x + dx[k],ty = a.y + dy[k];
		if (legal(tx,ty) && I[tx][ty] > tmp && (a.lx != tx || a.ly != ty)) {
			tmp = I[tx][ty];
			nx = tx,ny = ty,nk = k;
		}
	}
	++a.time;
	if (tmp != -inf) {
		if (a.time % 5 == 0) 
			do {
				nk = (nk+3) % 4;
				nx = a.x + dx[nk],ny = a.y + dy[nk];
			} while (!legal(nx,ny) || (a.lx == nx && a.ly == ny));
		a.lx = a.x,a.ly = a.y;
		a.x = nx,a.y = ny;
	}
	else a.lx = a.x,a.ly = a.y;
}

db dis(db x1,db y1,db x2,db y2) {
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

Ant FindTarget(const Tower &a) {
	if (Target != -1) 
		if (dis(a.x,a.y,A[Target].x,A[Target].y) <= r)
			return A[Target];
	int res = lA;
	For(i,lA+1,rA) 
		if (dis(a.x,a.y,A[i].x,A[i].y) < dis(a.x,a.y,A[res].x,A[res].y)) 
			res = i;

	return A[res];
}

db dis(db A,db B,db C,db x,db y) {
	return abs(A*x+B*y+C)/sqrt(A*A+B*B);
}

void Attack(const Tower & a) {
	Ant c = FindTarget(a);
	db _A,_B,_C;
	if (a.x != c.x) _A = (db)(a.y-c.y)/(db)(a.x-c.x),_B = -1,_C = (db)(a.y - (db)_A*a.x);
	else _A = 1,_B = 0,_C = -a.x;
	db nr = min((db)r,dis(a.x,a.y,c.x,c.y));
	For(i,lA,rA) 
		if (dis(a.x,a.y,A[i].x,A[i].y) <= nr && dis(_A,_B,_C,A[i].x,A[i].y) <= 0.5) 
			if ((A[i].x - a.x) * (A[i].x - c.x) <= 0)
				if ((A[i].y - a.y) * (A[i].y - c.y) <= 0)
					A[i].hp -= d;
}

void PickUp() {
	if (Target != -1) return ;
	For(i,lA,rA) 
		if (A[i].x == n && A[i].y == m) {
			Target = i;
			A[i].hp = min(A[i].hp + (A[i].ihp >> 1),A[i].ihp);
			return ;
		}
}

bool cmp(const Ant& A,const Ant& B) {
	return A.time > B.time;
}

void Die() {
	For(i,lA,rA) 
		if (A[i].hp < 0) {
			int tt = (Target != -1) ? A[Target].time : -1;Target = -1;
			A[i] = A[lA++];
			if (lA <= rA) sort(A + lA, A + rA + 1,cmp);
			For(j,lA,rA) if (tt == A[j].time) Target = j;
		}
}

void LeaveI() {
	For(i,lA,rA) 
		I[A[i].x][A[i].y] += (i == Target) ? 5 : 2;
}

int main() {
	setIO("test"); 
	
	fill(v,1);
	
	n = gi,m = gi;
	s = gi,d = gi,r = gi;
	rep(i,s) v[T[i].x = gi][T[i].y = gi] = 0;
	t = gi;
	
	lA = 0,rA = -1;
	
	int ans = -1;
	fill(I,0);
	rep(o,t) {
		if (rA - lA + 1 < 6 && NoAnt(0,0)) {
			++rA;
			A[rA].x = A[rA].y = A[rA].lx = A[rA].ly = 0;
			A[rA].time = 0;
			A[rA].t = Lcnt++;
			A[rA].hp = A[rA].ihp = (ll) 4 * Fast_Pow(1.1,A[rA].t/6+1);
		}
		
		LeaveI();
		
		For(i,lA,rA) Move(A[i]);
		
		PickUp();
		
		rep(i,s) Attack(T[i]);

		Die();		
		
		if (Target != -1 && A[Target].x == 0 && A[Target].y == 0) {
			For(i,lA,rA) --A[i].time;
			ans = o+1;
			break;
		}	
		rep(i,n+1) rep(j,m+1) if (I[i][j]) --I[i][j];
	}
	
	if (ans == -1) puts("The game is going on");
	else printf("Game over after %d seconds\n", ans);
	printf("%d\n", rA - lA + 1);
	For(i,lA,rA) printf("%d %d %lld %d %d\n", A[i].time, A[i].t/6+1,A[i].hp,A[i].x,A[i].y);
	
	return 0;
}
