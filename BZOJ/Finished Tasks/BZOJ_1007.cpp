/*
  Task: BZOJ_1007
  Created: 2012.02.24
  Author: Zhu Jiahao
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define For(i,a,b) for (i = a;i <= b;++i)

struct line
{
    int a,b;
}l[50001];

const double del=1e-6;
const int maxn=500000;
int i,j,k,f[2*maxn+1],n,num[2*maxn+1],ans[50001],st[50001],top=0;
bool cmp(line x,line y)
{
 	 return (x.a<y.a);
}

bool cmp2(int a,int b)
{
 	 return (a < b);
} 	 

inline bool check(double a,double b)
{
    if (fabs(a - b) <= del) return true;
    else if (a > b) return true;
    else return false;
}

inline bool pop(int x)
{
    double x1,x3;
    x3 = (double)(l[st[top]].b-l[st[top-1]].b)/(l[st[top-1]].a-l[st[top]].a);
    x1 = (double)(l[st[top]].b-l[x].b)/(l[x].a-l[st[top]].a);
    return (check(x3,x1));
}

int main()
{
    int a,b;
    scanf("%d",&n);
    For(i,-maxn,maxn) f[i + maxn]= -maxn-1;
    For(i,1,n) {
      scanf("%d %d",&a,&b);
      if (b > f[a+maxn]) {
          f[a+maxn] = b;
          num[a+maxn] = i;
      }
    }
    n = 0;
    For(i,-maxn,maxn)
      if (f[i+maxn]>-maxn-1) {
        l[++n].a = i;l[n].b = f[i+maxn];
      }
    sort(l+1,l+n+1,cmp);
    For(i,1,n) {
      for (;(top>=2)&&pop(i);) --top;
      st[++top] = i;
    }
    For(i,1,top) ans[i] = num[l[st[i]].a+maxn];
    sort(ans+1,ans+top+1,cmp2);
    For(i,1,top) {
      printf("%d",ans[i]);
      (i == top) ? printf("\n") : printf(" ");
    }
    
    return 0;
}
