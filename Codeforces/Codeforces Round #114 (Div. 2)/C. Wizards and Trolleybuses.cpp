/*
  Task: Wizards and Trolleybuses
  Created: 2012.03.28
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>

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
#define sqr(a) (a*a)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back

const int maxN = 100000+10;
int N;
double a,d,t,v;

int main()
{
	scanf("%d %lf %lf", &N, &a, &d);
	double now,last = 0;
	rep(i,N) {
      scanf("%lf %lf", &t, &v);
      now = t;
	  if (d > (sqr(v)/(a*2))) now += v/a+(d-sqr(v)/(a*2))/v;
	  else now += sqrt(2*d/a);
      if (last > now) now = last; else last = now;
      printf("%.8lf\n", now);
	}
	
	return 0;
}
