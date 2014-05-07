/*
  Task: D. Hit Ball
  Created: 2012.07.03
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int INF = 2147483647;
db a,b,m,vx,vy,vz;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool equal(db a,db b)
{
     return abs(a-b) < 0.00001;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%lf %lf %lf", &a, &b, &m);
 	scanf("%lf %lf %lf", &vx, &vy, &vz);
    db T = -m/vy;
    db nx = a/2,nz = 0;
    db tx,tz,nt;
    while (true) {
      if (vx == 0) tx = INF;
      else if (vx > 0) tx = (a-nx)/vx;
      else tx = -nx/vx;
      if (vz == 0) tz = INF;
      else if (vz > 0) tz = (b-nz)/vz;
      else tz = -nz/vz;
      nt = min(T,min(tx,tz));
      nx += nt*vx;nz += nt*vz;
      if (equal(nx,0) || equal(nx,a)) vx = -vx;
      if (equal(nz,0) || equal(nz,b)) vz = -vz;
      T -= nt;
      if (equal(T,0)) break;
    }
    printf("%.8lf %.8lf\n", nx, nz);
    
	return 0;
}
