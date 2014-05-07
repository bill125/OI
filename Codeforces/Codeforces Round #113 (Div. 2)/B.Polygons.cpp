/*
  Task:
  Created:
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define ll long long 

const int maxN = 100000+10,maxM = 2000+10;
int N,M;
ll Ax[maxN],Ay[maxN];

bool check(ll x,ll y,ll x1,ll y1,ll x2,ll y2)
{
 	 x2 -= x;x1 -= x;
 	 y2 -= y;y1 -= y;
       if ((double)y1*x2>(double)y2*x1) return true;
       else return false;
}

int main()
{
 	scanf("%d", &N);
 	rep(i,N) scanf("%I64d %I64d", &Ax[i], &Ay[i]);
 	scanf("%d", &M);
 	bool flag = true;
    rep(i,M) {
	  ll x,y;
	  scanf("%I64d %I64d", &x, &y);
	  rep(i,N) if (!check(Ax[i],Ay[i],Ax[(i+1)%N],Ay[(i+1)%N],x,y)) {
        flag = false; break;
      }
    }
    if (flag) printf("YES\n");
    else printf("NO\n");
	
	return 0;
}
