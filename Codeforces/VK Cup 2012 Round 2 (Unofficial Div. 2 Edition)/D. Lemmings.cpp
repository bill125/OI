/*
  Task: Lemmings
  Created: 2012.03.26
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld; 
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
#define pb push_back

const int maxN = 100000+10,maxM = 10000+10;
ll N,K,H;
int m[maxN],num[maxN],ans[maxN];
ll v[maxN];

bool cmp(int a,int b)
{
 	 return (m[a] > m[b] || (m[a] == m[b] && v[a] > v[b]));
}

bool check(double T)
{
	 ll now = 0;
	 repD(k,K) {
	   ans[k] = -1;
	   while (now < N) {
	     int j = num[now];
	     if ((double)v[j]*T >= (double)(k+1)*H) {
	       ans[k] = j;break;
	     }
	     ++now;
       }
       if (ans[k] == -1) return false;
       ++now;
     }
     return true;
}

int main()
{
	scanf("%I64d %I64d %I64d", &N, &K, &H);
	rep(i,N) scanf("%d", &m[i]);
	rep(i,N) scanf("%d", &v[i]);
	rep(i,N) num[i] = i;
	sort(num,num + N,cmp);
	double l = 0,r = 1000000007;
	rep(i,100) {
      double mid = (l + r) * 0.5;
      if (check(mid)) r = mid;
      else l = mid;
	}
	check(r);
	rep(i,K) {
      printf("%d", ans[i]+1);
      (i == K-1) ? printf("\n") : printf(" ");
    }
    
	return 0;
}
